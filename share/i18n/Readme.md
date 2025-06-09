# Linguistics
To edit linguistics *.ts files, use the QT Linguist
https://doc.qt.io/qt-6/qtlinguist-index.html


# Start Util Tool
run in WSL console the following command and open all *.ts files for translation.
´sudo linguist´

# Update TS files
To update TS files, run the ´QlockyApp_lupdate´ cmake target. In VSCode go to "CMake: Project Outline" and run the specific target (Custom task is created for that).

Ensure after update .ts files with linguist tool, the *.ts files are compiled to *.qm files with ´QlockyApp_lrelease´