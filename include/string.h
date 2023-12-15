#ifndef STRUCTSPP_PROJECT_STRING_H
#define STRUCTSPP_PROJECT_STRING_H
#include <yvals_core.h>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>

namespace utils{
    class string{
    private:
        size_t _long = 10;
        char *s=new char[_long];
        size_t length=0;
        void flash_size(size_t newsize){
            char *c = s;
            delete []s;
            s = new char[newsize];
            strcpy(s, c);
            _long = newsize;
            delete []c;
        }
        void flash(size_t newsize, const char* newstr){
            flash_size(strlen(newstr)+1);
            strcpy(s, newstr);
            this->length = strlen(newstr);
        }
    public:
        size_t strlen(){
            size_t i=0;
            while(s[i]!='\0')i++;
            return i;
        }
        static size_t strlen(const char *c){
            size_t i = 0;
            while (c[i]!='\0')i++;
            return i;
        }
        string():length(0){}
        string(const char* c){
            flash(string::strlen(c)+1, c);
        }
        void operator=(string str){
            flash(str._long, str.s);
        }
        char operator[](size_t i){
            return this->s[i];
        }
        bool operator==(string str){
            return stramt(str);
        }
        bool operator!=(string str){
            return !stramt(str);
        }
        void strcpyto(string t){
            t.flash(this->_long, this->s);
        }
        void strcpyto(char* t){
            t = this->s;
        }
        void strcpyin(string f){
            this->flash(f._long, f.s);
            this->length = f.length;
        }
        bool empty(){
            if (length == 0) return true;
            return false;
        }
        void clear(){
            s = NULL;
            this->length = 0;
        }
        char* data(){
            return s;
        }
        bool substr(string sub){
            return strstr(this->s, sub.s);
        }
        bool substr(char* sub){
            return strstr(this->s, sub);
        }
        bool substr(const char* sub){
            return strstr(this->s, sub);
        }
        friend bool substr(char* str, string sub){
            return strstr(str, sub.s);
        }
        friend bool substr(const char* str, string sub){
            return strstr(str, sub.s);
        }
        bool stramt(string str){
            return strcmp(str.s, this->s);
        }
        size_t size(){
            return length;
        }
        ~string(){
            delete[] s;
        }
        operator int(){
            return std::stoi(s);
        }
        operator long(){
            return std::stol(s);
        }
        operator double(){
            return std::stod(s);
        }
        operator float(){
            return std::stof(s);
        }
        operator long long(){
            return std::stoll(s);
        }
        operator unsigned long(){
            return std::stoul(s);
        }
        operator unsigned long long (){
            return std::stoull(s);
        }
        string operator+(string l){
            string ret;
            ret._long = this->_long + l._long;
            ret.length = this->length + l.length;
            ret.s = new char[ret._long];
            strcpy(ret.s, strcat(this->s, l.s));
        }
        friend void operator<<(std::ostream &out, string str){
            out << str.s;
        }
        friend std::istream& operator>>(std::istream& in, string& str) {
            std::vector<char> temp;
            char ch;
            while (in.get(ch) && ch != '\n') {
                temp.push_back(ch);
            }
            temp.push_back('\0');
            str.flash_size(temp.size());
            std::copy(temp.begin(), temp.end(), str.s);
            str.length = temp.size() - 1;
            return in;
        }
    };
}
#endif //STRUCTSPP_PROJECT_STRING_H
