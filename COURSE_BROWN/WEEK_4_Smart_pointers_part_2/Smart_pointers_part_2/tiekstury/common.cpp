#include "Common.h"
using namespace std;

//класс фигуры
class Rectangle: public IShape {
public:
  virtual  std::unique_ptr<IShape> Clone() const{
        auto x = MakeShape(ShapeType::Rectangle);
        x.get()->SetPosition(this->GetPosition());
        x.get()->SetSize(this->GetSize());
        x.get()->SetTexture(this->texture);
        return move(x);
  }
  virtual void SetPosition(Point x){
        point_ = x;
  }
  virtual Point GetPosition() const{
        return point_;
  }
  virtual void SetSize(Size x){
        size_ = x;
  }
  virtual Size GetSize() const{
        return size_;
  }
  virtual void SetTexture(std::shared_ptr<ITexture> x){
        texture = x;
  }

  virtual ITexture* GetTexture() const {
        return texture.get();
  }

  virtual void Draw(Image& image) const{
        int length_y = point_.y+size_.height;
        int length_x = point_.x+size_.width;
        if(!texture){
            for(size_t i = point_.y ; i<(length_y);i++){
                for(size_t j = point_.x ; j<(length_x);j++){
                    if(i<image.size()&&j<image[0].size()){
                        image[i][j] ='.';
                    }
                }
            }
        }else{
            Image img = texture.get()->GetImage();
            Size sze = texture.get()->GetSize();
            for(size_t i = point_.y ; i<(length_y);i++){
                for(size_t j = point_.x ; j<(length_x);j++){
                     if(i<image.size()&&j<image[0].size()){
                        if((j-point_.x<sze.width)&&(i-point_.y<sze.height)){
                            image[i][j]= img[i-point_.y][j-point_.x];
                        }else {
                            image[i][j] ='.';
                        }
                     }
                }
            }
        }
  }
  std::shared_ptr<ITexture>texture;
private:
    Point point_;
    Size size_;

};

class Ellipse: public IShape {
public:
  virtual  std::unique_ptr<IShape> Clone() const{
        auto x = MakeShape(ShapeType::Ellipse);
        x.get()->SetPosition(this->GetPosition());
        x.get()->SetSize(this->GetSize());
        x.get()->SetTexture(this->texture);
        return move(x);
  }
  virtual void SetPosition(Point x){
        point_ = x;
  }
  virtual Point GetPosition() const{
        return point_;
  }
  virtual void SetSize(Size x){
        size_ = x;
  }
  virtual Size GetSize() const{
        return size_;
  }
  virtual void SetTexture(std::shared_ptr<ITexture> x){
        texture = x;
  }

  virtual ITexture* GetTexture() const {
        return texture.get();
  }

  virtual void Draw(Image& image) const{
        int length_y = point_.y+size_.height;
        int length_x = point_.x+size_.width;
        if(!texture){
            for(size_t i = point_.y ; i<(length_y);i++){
                for(size_t j = point_.x ; j<(length_x);j++){
                    if(i<image.size()&&j<image[0].size()){
                        if(IsPointInEllipse({j-point_.x,i-point_.y},size_)){
                            image[i][j] ='.';
                        }
                    }
                }
            }
        }else{
            Image img = texture.get()->GetImage();
            Size sze = texture.get()->GetSize();
            for(size_t i = point_.y ; i<(length_y);i++){
                for(size_t j = point_.x ; j<(length_x);j++){
                    if(i<image.size()&&j<image[0].size()){
                        if((j-point_.x<sze.width)&&(i-point_.y<sze.height)){
                            if(IsPointInEllipse({j-point_.x,i-point_.y},size_)){
                                image[i][j]= img[i-point_.y][j-point_.x];
                            }
                        }else {
                            if(IsPointInEllipse({j-point_.x,i-point_.y},size_)){
                                image[i][j] ='.';
                            }
                        }
                    }
                }
            }
        }
  }

    std::shared_ptr<ITexture>texture;
private:
    Point point_;
    Size size_;
};


std::unique_ptr<IShape> MakeShape(ShapeType shape_type){
    if(shape_type == ShapeType::Rectangle){
        return make_unique<Rectangle>();

    }else if(shape_type ==ShapeType::Ellipse){
        return make_unique<Ellipse>();
    }
}
