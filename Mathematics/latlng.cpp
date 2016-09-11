/* latitude & longitude */
class latlng
{
private:
  typedef double value_type;
  const double PI = std::acos(-1.0);

public:
  latlng() : _lat(0.0), _lng(0.0), _R(0.0) {}
  explicit latlng(value_type lat, value_type lng, value_type radius = 0.0) : _lat(lat), _lng(lng), _R(radius) {}
  ~latlng() {}

  value_type lat() const noexcept { return _lat; }
  value_type lng() const noexcept { return _lng; }
  value_type radius() const noexcept { return _R; }
  value_type R() const noexcept { return _R; }

  std::pair<value_type, value_type> latLng() const noexcept { return std::make_pair(_lat, _lng); }
  std::tuple<value_type, value_type, value_type> get() const noexcept { return std::make_tuple(_lat, _lng, _R); }

  /*
  template <typename T>
  struct point { T x, y, z; };
  */
  point<value_type> to_point()
  {
    point<value_type> p;

    value_type x = _R * std::cos(_lng * PI / 180) * std::cos(_lat * PI / 180);
    value_type y = _R * std::sin(_lng * PI / 180) * std::cos(_lat * PI / 180);
    value_type z = _R * std::sin(_lat * PI / 180);
  }

private:
  value_type _lat, _lng;
  value_type _R;
};
