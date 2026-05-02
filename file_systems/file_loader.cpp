#include "file_loader.hpp"
#include <fstream> 

namespace cg
{
FileContents::FileContents(){
    size = 0;
    data = nullptr;
};

FileContents::~FileContents()
{
    destroy();
}

void FileContents::init(uint32_t size_in){

    destroy(); // prevents memory leak if init is called twice

    size = size_in;
    // dynamically allocate memory for file contents
    // allocate one extra byte
    // this allows us to store the null terminator '\0'
    data = new char[size+1];

}

void FileContents::destroy(){

    delete[] data; // safe even if data == nullptr
    data = nullptr;
    size = 0;
}

bool load_file_contents(const std::string &path, FileContents &file_contents){
    /*
    Create an input file stream object and open the file 
    std::ios::binary means read the file exactly as it is

    Move the file pointer to the END of the file - this way we can figure 
    out how big the file is. tellg() tells us the current position of the pointer, and since we are at the 
    end, this position = file size

    Convert file size into an unsigned integer and allocate enugh memory to store the file contents

    Move the file pointer back to the BEGINNING of the file so we can 
    acutally read from the start. Read entire file into memory and store it inside
    of file_contents.data

    Add a null terminator at the end
    This allows the data to be treated like a C-style string
    */
    std::ifstream ifs(path, std::ios::binary);

    if(!ifs.is_open()){
        return false;
    }

    ifs.seekg(0, std::ios::end);
    std::streampos end = ifs.tellg();

    if (end < 0) return false;

    uint32_t size = static_cast<uint32_t>(end);
    file_contents.init(size);

    ifs.seekg(0, std::ios::beg);
    ifs.read(file_contents.data, size);

    if(!ifs && size != 0)
    {
        file_contents.destroy();
        return false;
    }

    file_contents.data[size] = '\0';
    return true;
}


} // namespace cg