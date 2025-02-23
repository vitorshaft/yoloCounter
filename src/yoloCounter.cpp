#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <fstream> // Incluído o cabeçalho <fstream>

// Função para carregar a lista de classes
std::vector<std::string> load_class_list() {
    std::vector<std::string> class_list;
    std::ifstream ifs("config_files/classes.txt");
    if (!ifs.is_open()) {
        std::cerr << "Erro ao abrir o arquivo classes.txt!" << std::endl;
        return class_list;
    }
    std::string line;
    while (getline(ifs, line)) {
        class_list.push_back(line);
    }
    return class_list;
}

// Função para carregar a rede YOLO
void load_net(cv::dnn::Net &net, bool is_cuda) {
    std::string cfgFile = "config_files/yolov4-tiny.cfg";
    std::string weightsFile = "config_files/yolov4-tiny.weights";

    std::cout << "Carregando arquivo de configuração: " << cfgFile << std::endl;
    std::cout << "Carregando arquivo de pesos: " << weightsFile << std::endl;

    auto result = cv::dnn::readNetFromDarknet(cfgFile, weightsFile);
    if (result.empty()) {
        std::cerr << "Erro ao carregar a rede YOLO!" << std::endl;
        return;
    }

    if (is_cuda) {
        std::cout << "Tentando usar CUDA\n";
        result.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
        result.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA_FP16);
    } else {
        std::cout << "Executando na CPU\n";
        result.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
        result.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    }
    net = result;
}

// Função principal
int main() {
    // Carrega a lista de classes
    std::vector<std::string> class_list = load_class_list();

    // Inicializa a webcam
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Erro ao abrir a webcam!" << std::endl;
        return -1;
    }

    // Carrega a rede YOLO
    cv::dnn::Net net;
    load_net(net, false); // Use true para CUDA, se disponível

    // Define a ROI (Região de Interesse)
    cv::Rect roi(200, 100, 300, 300); // Ajuste conforme necessário
    std::map<int, bool> objectInsideROI; // Rastreia se um objeto está dentro da ROI
    int totalObjectCount = 0; // Contador total de objetos que já entraram na ROI
    int currentObjectCount = 0; // Contador de objetos atualmente dentro da ROI

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Erro ao capturar frame da webcam!" << std::endl;
            break;
        }

        // Prepara a imagem para a rede YOLO
        cv::Mat blob;
        cv::dnn::blobFromImage(frame, blob, 1 / 255.0, cv::Size(416, 416), cv::Scalar(), true, false);
        net.setInput(blob);

        // Obtém as saídas da rede
        std::vector<cv::Mat> outputs;
        net.forward(outputs, net.getUnconnectedOutLayersNames());

        // Processa as detecções
        std::vector<int> classIds;
        std::vector<float> confidences;
        std::vector<cv::Rect> boxes;
        for (const auto& output : outputs) {
            for (int i = 0; i < output.rows; i++) {
                const cv::Mat& detection = output.row(i);
                cv::Mat scores = detection.colRange(5, output.cols);
                cv::Point classIdPoint;
                double confidence;
                cv::minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);

                if (confidence > 0.5) { // Limiar de confiança
                    int centerX = static_cast<int>(detection.at<float>(0) * frame.cols);
                    int centerY = static_cast<int>(detection.at<float>(1) * frame.rows);
                    int width = static_cast<int>(detection.at<float>(2) * frame.cols);
                    int height = static_cast<int>(detection.at<float>(3) * frame.rows);
                    int left = centerX - width / 2;
                    int top = centerY - height / 2;

                    classIds.push_back(classIdPoint.x);
                    confidences.push_back(static_cast<float>(confidence));
                    boxes.push_back(cv::Rect(left, top, width, height));
                }
            }
        }

        // Aplica supressão não máxima
        std::vector<int> indices;
        cv::dnn::NMSBoxes(boxes, confidences, 0.5, 0.4, indices);

        // Verifica se os objetos estão dentro da ROI
        currentObjectCount = 0; // Reinicia o contador de objetos atuais
        for (int index : indices) {
            cv::Rect box = boxes[index];
            cv::Point center(box.x + box.width / 2, box.y + box.height / 2);

            if (roi.contains(center)) {
                if (!objectInsideROI[index]) {
                    objectInsideROI[index] = true;
                    totalObjectCount++; // Incrementa o contador total
                }
                currentObjectCount++; // Incrementa o contador atual
            } else {
                objectInsideROI[index] = false;
            }

            // Desenha a caixa delimitadora e o rótulo
            cv::rectangle(frame, box, cv::Scalar(0, 255, 0), 2);
            cv::putText(frame, class_list[classIds[index]], cv::Point(box.x, box.y - 10),
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
        }

        // Desenha a ROI
        cv::rectangle(frame, roi, cv::Scalar(0, 0, 255), 2);

        // Exibe a contagem de objetos
        cv::putText(frame, "Total de objetos: " + std::to_string(totalObjectCount), cv::Point(10, 30),
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        cv::putText(frame, "Objetos na ROI: " + std::to_string(currentObjectCount), cv::Point(10, 70),
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);

        // Exibe o frame
        cv::imshow("yoloCounter", frame);

        // Pressione ESC para sair
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}