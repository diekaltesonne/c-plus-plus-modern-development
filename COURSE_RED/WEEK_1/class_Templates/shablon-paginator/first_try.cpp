using namespace std;

template <typename Iterator>
class PageRange{
public:
    PageRange(const size_t& size,Iterator& begin , Iterator& end):_size(size),_begin(begin),_end(end){
    }
    size_t size() const{
        return _size;
    }
    const auto begin() const{
        return _begin;
    }
    const auto end()   const{
        return _end;
    }
private:
    Iterator _begin;
    Iterator _end;
    size_t _size;
};

template <typename Iterator>
class Paginator{
public:

    Paginator(Iterator& begin , Iterator& end, size_t& size_of_page):_begin(begin),_end(end)
    ,_page_size(size_of_page){

        for (auto begin = _begin; begin < _end; begin += _page_size) {
            auto end = begin + size > _end ? _end : begin + size;
            pages.push_back(
                { begin, end, static_cast<size_t>(distance(begin, end)) }
            );
        }

    }

    //    vector<PageRange<Iterator>> split(){
    //        vector<PageRange<Iterator>> result;

    //        size_t size_ = distance(_begin,_end);
    //        size_t max_size = distance(_begin,_end)/_page_size;

    //        for(size_t i = 0; i <= max_size; i++){
    //            auto current = _begin + size * i;
    //            result.push_back({current, current + min(size_ - i * size, _page_size)});
    //        }
    //        return result;

    //    }



    size_t size() const{
        return size_t(distance(_begin,_end)/_page_size);
    }

    Iterator begin() {
        return pages.begin();
    }
    Iterator end() {
        return pages.end();
    }
private:
    vector<PageRange<Iterator>> pages;
    const Iterator _begin;
    const Iterator _end;
    size_t _page_size;
};

//
template <typename C>
auto Paginate(C& c, size_t page_size) {
     return Paginator{ c.begin(), c.end(), page_size };
}

//NOT MY TRY
template <typename Iterator>
class Page {
private:
  Iterator first;
  Iterator last;
  size_t page_size;

public:
  Page(Iterator f, Iterator l, size_t s)
  : first(f)
  , last(l)
  , page_size(s)
  {}

  Iterator begin() const{
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return page_size;
  }
};

// Write class template Paginator
template <typename Iterator>
class Paginator {
private:
  vector<Page<Iterator>> pages;

public:
  Paginator(Iterator first, Iterator last, size_t size) {
    for (auto begin = first; begin < last; begin += size) {
      auto end = begin + size > last ? last : begin + size;

      pages.push_back(
        { begin, end, static_cast<size_t>(distance(begin, end)) }
      );

    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

// Write function template Paginate
template <typename C>
auto Paginate(C& c, size_t page_size) {
     return Paginator{ c.begin(), c.end(), page_size };
}
