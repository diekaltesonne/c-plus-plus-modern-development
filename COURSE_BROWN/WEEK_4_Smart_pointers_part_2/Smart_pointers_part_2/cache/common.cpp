#include "Common.h"
#include <unordered_map>
#include <list>
#include <map>
#include <mutex>
// Интерфейс, представляющий книгу
using namespace std;

//Кэширование производится методом вытеснения давно неиспользуемых элементов (Least Recently Used, LRU).
//Каждый элемент кэша имеет ранг. При вызове метода GetBook(),
//если книга с таким названием уже есть в кэше, её ранг поднимается до максимального (строго больше, чем у всех остальных).
//Если такой книги нет в кэше, то она добавляется в кэш, и её ранг, опять же, выставляется в максимальный.
//При этом, если общий размер книг превышает ограничение max_memory, из кэша удаляются книги с наименьшим рангом, пока это необходимо.
//Возможно, пока он полностью не будет опустошён. Если же размер запрошенной книги уже превышает max_memory, то после вызова метода кэш остаётся пустым,
//то есть книга в него не добавляется.

//!!!WARNING!!!
//Метод GetBook() может вызываться одновременно из нескольких потоков, поэтому необходимо обеспечить ему безопасность работы в таких условиях.
//Используемые на практике реализации LRU кэшей позволяют искать элементы по ключу и удалять давно неиспользуемые элементы за константное время.
//В данной задаче этого не требуется. Искать давно неиспользуемые элементы можно перебором всех имеющихся.
//!!!WARNING!!!

class Cache:public ICache {
public:
    Cache(std::shared_ptr<IBooksUnpacker> books_unpacker,const ICache::Settings& settings):settings_(settings),books_unpacker_(books_unpacker){

    }

    // Возвращает книгу с заданным названием. Если её в данный момент нет
    // в кэше, то предварительно считывает её и добавляет в кэш. Следит за тем,
    // чтобы общий объём считанных книг не превосходил указанного в параметре
    // max_memory. При необходимости удаляет из кэша книги, к которым дольше всего
    // не обращались. Если размер самой книги уже больше max_memory, то оставляет
    // кэш пустым.

    virtual BookPtr GetBook(const std::string& book_name){
        const lock_guard<mutex> lock(m);
        if(cashe.count(book_name)!=0){
            if(cashe.at(book_name)!=cashe_vault.begin()){
                cashe_vault.push_front(move(*cashe.at(book_name)));
                cashe_vault.erase(cashe.at(book_name));
                cashe[book_name]=cashe_vault.begin();
            }
            return *cashe.at(book_name);
        }else{
            BookPtr book = books_unpacker_.get()->UnpackBook(book_name);
            if(book.get()->GetContent().size()>settings_.max_memory){
                return book;
            }else{
                memory+=book.get()->GetContent().size();
                while(memory>settings_.max_memory){
                    cashe.erase(cashe_vault.back().get()->GetName());
                    memory-=cashe_vault.back().get()->GetContent().size();
                    cashe_vault.pop_back();
                }
                cashe_vault.push_front(move(book));
                cashe.insert(make_pair(book_name,cashe_vault.begin()));
                return (*cashe.at(book_name));
            }
        }
    }
    Settings settings_;
private:
    shared_ptr<IBooksUnpacker> books_unpacker_;
    mutex m;
    list<BookPtr>cashe_vault;
    size_t memory =0 ;
    unordered_map<string, list<BookPtr>::iterator> cashe;
};

// Для создания объекта ICache используется функция MakeCache(),
// которую вам необходимо реализовать. Она принимает объект IBooksUnpacker,
// а также объект ICache::Settings - настройки кэша.
// В нашей задаче настройки содержат всего один параметр max_memory
// — максимальный суммарный размер всех книг в кэше в байтах, —
// но в реальности их может быть больше.
// Именно поэтому мы оформили настройки в виде структуры.
// Размером книги считается размер её текста в байтах.
// Создаёт объект кэша для заданного распаковщика и заданных настроек

std::unique_ptr<ICache> MakeCache(std::shared_ptr<IBooksUnpacker> books_unpacker,const ICache::Settings& settings){
    return std::make_unique<Cache>(books_unpacker,settings);
}
