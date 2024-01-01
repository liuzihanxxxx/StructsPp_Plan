#ifndef STRUCTSPP_PROJECT_FILE_H
#define STRUCTSPP_PROJECT_FILE_H

#include <fstream>
#include <filesystem>
#include "string.h"

using namespace std;
namespace utils {
    class file {
    protected:
        FILE *open;

        struct _file {
            class nullfile : public exception {
            public:
                const char *what() const noexcept override {
                    return "cannot open file: unknow file!\n"
                           "maybe file does not exist or you did not provide sufficient permissions.\n";
                }

                nullfile() = default;
            };

            string name;
            string mode;
            bool isfail;
            FILE *file;

            ifstream *in = nullptr;
            ofstream *out = nullptr;

            _file() = default;

            _file(string name, string mode) {
                isfail = fopen(name.c_str(), mode.c_str()) == nullptr;
                if (isfail) {
                    std::cerr << ferror(fopen(name.c_str(),
                                              mode.c_str())) << std::endl;

                    throw nullfile();
                } else {
                    file = fopen(name.c_str(), mode.c_str());
                }
            }
        } *_openFile;

        enum stream {
            in,
            out
        };
        class bad_input : public exception {
        public:
            const char* what() const noexcept{
                return "cannot input/input error!\n"
                       "maybe file does not exist or you did not provide sufficient permissions.\n";
            }
        };
        class bad_output : public exception{
        public:
            const char* what() const noexcept{
                return "cannot output/output error!\n"
                       "maybe file does not exist or you did not provide sufficient permissions.\n";
            }
        };
        static bool isnnull(stream s, _file *file) {
            switch (s) {
                case in:
                    if (file->in == nullptr)  throw bad_input();
                case out:
                    if (file->out == nullptr) throw bad_output();
            }
        }

        class fileinstream {
        private:
            _file *open;
        public:
            friend class string;

            fileinstream() = delete;

            fileinstream(string name, string mode) {
                open = new _file(name, mode);
            }

            void *operator new(size_t size) = delete;

            void operator delete(void *p) = delete;

            void *operator new[](size_t size) = delete;

            void operator delete[](void *p) = delete;

            template<typename T>
            requires requires(T t){
                { *open->in >> t };
            }
            void operator>>(T &p) {
                isnnull(in, open);
                open->in >> p;
            }

            void __stdcall getline(utils::string &s, size_t count) {
                isnnull(in, open);
                char *c = new char[count + 1];
                open->in->getline(c, count);
                s.strcpyin(c);
                delete[]c;
            }

            void __stdcall getline(char *&cs, size_t count) {
                isnnull(in, open);
                open->in->getline(cs, count);
            }

            void __stdcall getline(std::string &s, size_t count) {
                isnnull(in, open);
                char *c = new char[count + 1];
                open->in->getline(c, count);
                s.assign(c, open->in->gcount());
                delete[]c;
            }

            void __stdcall get(utils::string &s){
                char c[1];
                open->in->get(c[0]);
                s.flash(1, c);
            }

            ~fileinstream() {
                fclose(open->file);
                delete open->in;
                delete open;
            }
        };

        class fileoutstream {
            //todo make ok this type
        };

    public:
        static fileinstream fin;
        static fileoutstream fout;

        file() = delete;

        file(string name, string mode) {
            _openFile = new _file(name, mode);
            open = _openFile->file;
            fin = fileinstream(name, mode);
        }
    };
}

#endif //STRUCTSPP_PROJECT_FILE_H
