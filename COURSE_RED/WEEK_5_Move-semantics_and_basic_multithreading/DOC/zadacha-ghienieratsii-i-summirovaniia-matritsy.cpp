#include <future>
int main(){
  LOG_DURATION("Total");
  const size_t matrix_size = 7000;
  vector<vector<int>> matrix
  {
    LOG_DURATION("Single thread generation");
    matrix = GenerateSingleThread(matrix_size);
  }
  {
    LOG_DURATION("Single thread sum");
    matrix = SumSingleThread(matrix_size);
  }
}
vector<vector<int>>GenerateMultiThread(
  size_t size,size_t page_size){
    size_t first_row  = 0;
    vector<vector<int>> result(size);
    vector <future<void>> futures;
    for (auto page: Paginate(result,page_size)){
      futures.push_back(async([page,first_row,size]{GenerateSingleThread(page,first_row)}));
      first_row += page_size;
    }
    return result;
}
