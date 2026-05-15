#include "mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QImage>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Huffman Archiver Pro");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnBrowse_clicked()
{
    selectedFile = QFileDialog::getOpenFileName(this,
                                                "Select Text File",
                                                "",
                                                "Text Files (*.txt);;All Files (*)");
    if (!selectedFile.isEmpty()) {
        // Use lblStats because that's the name in your UI designer
        ui->lblStats->setText("Selected: " + selectedFile);
        updateStatus("File loaded. Ready to compress.");
    }
}

void MainWindow::on_btnCompress_clicked()
{
    if (selectedFile.isEmpty()) {
        updateStatus("Error: No file selected!", true);
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(this,
                                                    "Save Compressed File",
                                                    "",
                                                    "Huf Files (*.huf)");
    if (savePath.isEmpty())
        return;

    if (compressor.compress(selectedFile.toStdString(), savePath.toStdString())) {
        updateStatus("Compression Successful!");

        // Update Stats using the correct backend variable: compressor
        auto stats = compressor.getStats();
        ui->lblStats->setText(QString("Ratio: %1% | Saved: %2 bits")
                                  .arg(stats.ratio, 0, 'f', 2)
                                  .arg(stats.originalSize - stats.compressedSize));

        // Display Codes
        ui->txtCodes->clear();
        for (auto const &[ch, code] : compressor.getCodes()) {
            ui->txtCodes->append(QString("'%1' : %2").arg(ch).arg(QString::fromStdString(code)));
        }
    } else {
        updateStatus("Compression Failed. Check if file is empty.", true);
    }
}

void MainWindow::on_btnDecompress_clicked()
{
    QString inputPath = QFileDialog::getOpenFileName(
        this,
        "Select Compressed File",
        "",
        "Huf Files (*.huf)"
        );

    if (inputPath.isEmpty())
        return;

    QString outputPath = QFileDialog::getSaveFileName(
        this,
        "Save Decompressed File",
        "",
        "Text Files (*.txt)"
        );

    if (outputPath.isEmpty())
        return;

    // Use the saved Huffman tree from compression
    bool ok = compressor.decompress(
        inputPath.toStdString(),
        outputPath.toStdString(),
        compressor.getRoot()
        );

    if (ok) {
        updateStatus("Decompression Successful!");
        QMessageBox::information(this, "Success",
                                 "File decompressed successfully!");
    } else {
        updateStatus("Decompression Failed!", true);
        QMessageBox::critical(this, "Error",
                              "Could not decompress file.");
    }
}
void MainWindow::updateStatus(const QString &message, bool isError)
{
    // This updates the lblStats since we don't have a separate lblStatus
    ui->lblStats->setText(message);
    ui->lblStats->setStyleSheet(isError ? "color: red;" : "color: green;");

}
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>

#include <QFileDialog>
#include <QMessageBox>
#include <QImage>

void MainWindow::on_btnPngCompress_clicked()
{
    QString inputPath = QFileDialog::getOpenFileName(
        this,
        "Select Image",
        "",
        "Images (*.png *.jpg *.jpeg)"
        );

    if (inputPath.isEmpty())
        return;

    QImage image(inputPath);

    if (image.isNull()) {
        QMessageBox::warning(this, "Error", "Could not load image.");
        return;
    }

    QString outputPath = QFileDialog::getSaveFileName(
        this,
        "Save Compressed Image",
        "",
        "JPEG Image (*.jpg)"
        );

    if (outputPath.isEmpty())
        return;

    // 🔥 Resize (biggest real compression factor)
    image = image.scaled(
        image.width() * 0.7,
        image.height() * 0.7,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );

    // JPEG compression (0–100 quality)
    bool ok = image.save(outputPath, "JPG", 75);

    if (ok)
        QMessageBox::information(this, "Success", "Compression done!");
    else
        QMessageBox::critical(this, "Error", "Compression failed!");
}