int main () {
vector <int > v = {1, 2, 3, 4, 5};
for (int x : Head(v, 3)) {
cout << x << " ";
}
}

template <typename T>
vector <T> Head(vector <T >& v, size_t top) {
return {
v.begin () ,
next(v.begin () , min(top , v.size ()))
};
}


template <typename T>
size_t RangeSize ( IteratorRange <T> r) {
return r.end () − r. begin ();
}



template <typename Iterator >
IteratorRange <Iterator > MakeRange ( Iterator begin , Iterator end) {
return IteratorRange <Iterator >( begin , end);
}

auto second_half = MakeRange {
v.begin () + v.size () / 2, v.end ()
};

#define ASSERT_EQUAL(x, y) {                    \
  auto z = x;                                   \
  ASSERT_EQUAL_EMBEDDED(z, y, x)                \
}

#define ASSERT_EQUAL_EMBEDDED(x, y, old_x) {    \
  ostringstream os;                             \
  os << #old_x << " != " << #y << ", "          \
     << __FILE__ << ":" << __LINE__;            \
  AssertEqual((x), (y), (os.str()));            \
}

#define ASSERT_EQUAL(x, y) {                             \
	auto calculated_x = x; auto calculated_y = y; {    	   \
    ostringstream os;                                    \
    os << #x << " != " << #y << ", "                     \
  	  << __FILE__ << ":" << __LINE__;                    \
    AssertEqual(calculated_x, calculated_y, os.str());   \
  }										                                   \
}
