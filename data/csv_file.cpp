#include "csv_file.h"


/* =================================
 *               PUBLIC
 *  =================================*/

CsvFile::CsvFile(std::string const &fileDir) {
    outputDir = fileDir;
}

void CsvFile::addRow(CsvRow const &row) {
    rows.push_back(row);
}

void CsvFile::write() const {
    unsigned int i = 0;
    std::string fileName = outputDir + "experiment_";
    std::ifstream fileOpener(fileName + std::to_string(i));
    while(fileOpener.is_open())fileOpener = std::ifstream(fileName + std::to_string(++i));
    fileOpener.close();
    std::ofstream file(fileName + std::to_string(i), std::ios::out);
    for(auto const& row : rows){
        std::string currentRow;
        for(auto const& value : row){
            currentRow += value + ",";
        }
        file << currentRow << "\n";
    }
    file.close();
}
