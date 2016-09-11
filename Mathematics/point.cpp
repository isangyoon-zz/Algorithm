template <typename T>
class point
{
private:
  typedef T value_type;
  const double PI = std::acos(-1.0);

public:
  point() : _x(0), _y(0), _z(0) {}
  explicit(value_type x, value_type y, value_type z) : _x(x), _y(y), _z(z) {}
  ~point() {}

  value_type x() const noexcept { return _x; }
  value_type y() const noexcept { return _y; }
  value_type z() const noexcept { return _z; }

  std::tuple<value_type, value_type, value_type> get() const noexcept { return std::make_tuple(_x, _y, _z); }

  latlng to_latlng()
  {
    double r = std::sqrt(_x * _x + _y * _y + _z * _z);
    double lat = 180 / PI * std::asin(_z / r);
    double lng = 180 / PI * std::acos(_x / std::sqrt(_x * _x + _y * _y));

    return latlng(lat, lng, r);
  }

private:
  value_type _x;
  value_type _y;
  value_type _z;
};
