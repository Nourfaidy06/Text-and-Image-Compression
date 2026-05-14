#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Huffman Archiver Pro");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnBrowse_clicked() {
    selectedFile = QFileDialog::getOpenFileName(this, "Select Text File", "", "Text Files (*.txt);;All Files (*)");
    if (!selectedFile.isEmpty()) {
        // Use lblStats because that's the name in your UI designer
        ui->lblStats->setText("Selected: " + selectedFile);
        updateStatus("File loaded. Ready to compress.");
    }
}

void MainWindow::on_btnCompress_clicked() {
    if (selectedFile.isEmpty()) {
        updateStatus("Error: No file selected!", true);
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(this, "Save Compressed File", "", "Huf Files (*.huf)");
    if (savePath.isEmpty()) return;

    if (compressor.compress(selectedFile.toStdString(), savePath.toStdString())) {
        updateStatus("Compression Successful!");

        // Update Stats using the correct backend variable: compressor
        auto stats = compressor.getStats();
        ui->lblStats->setText(QString("Ratio: %1% | Saved: %2 bits")
                                  .arg(stats.ratio, 0, 'f', 2)
                                  .arg(stats.originalSize - stats.compressedSize));

        // Display Codes
        ui->txtCodes->clear();
        for (auto const& [ch, code] : compressor.getCodes()) {
            ui->txtCodes->append(QString("'%1' : %2").arg(ch).arg(QString::fromStdString(code)));
        }
    } else {
        updateStatus("Compression Failed. Check if file is empty.", true);
    }
}

void MainWindow::on_btnDecompress_clicked() {
    // You can implement decompression logic here later
    updateStatus("Decompression feature coming soon!");
}

void MainWindow::updateStatus(const QString& message, bool isError) {
    // This updates the lblStats since we don't have a separate lblStatus
    ui->lblStats->setText(message);
    ui->lblStats->setStyleSheet(isError ? "color: red;" : "color: green;");
}
