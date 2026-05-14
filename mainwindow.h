#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "huffman.h" // Includes your compression logic

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // These functions run when you click the buttons in the UI
    void on_btnBrowse_clicked();
    void on_btnCompress_clicked();
    void on_btnDecompress_clicked();

private:
    Ui::MainWindow *ui;
    Huffman compressor;   // The backend engine
    QString selectedFile; // To store the path of the file you pick

    // Helper to show messages in the GUI status label
    void updateStatus(const QString &msg, bool isError = false);
};
#endif // MAINWINDOW_H
