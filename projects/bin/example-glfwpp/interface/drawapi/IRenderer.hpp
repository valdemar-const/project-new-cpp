#pragma once

#include <vector>
#include <string_view>
#include <utility>

namespace drawapi
{

template<typename T>
struct IPoint2d
{
  public: // type traits

    using Value_Type = T;

  public:

    T x;
    T y;
};

struct IMaterial
{
    virtual void get_point_width()         = 0;
    virtual void get_line_width()          = 0;
    virtual void get_line_style()          = 0;
    virtual void get_fill_color()          = 0;
    virtual void get_border_color()        = 0;
    virtual void get_border_width()        = 0;
    virtual void get_text_font()           = 0;
    virtual void get_text_alignment()      = 0;
    virtual void get_text_direction()      = 0;
    virtual void get_text_alpha_space()    = 0;
    virtual void get_subdivision_level()   = 0;
    virtual void get_multisampling_level() = 0;
};

struct IImage; // forward decl
struct IVideo; // forward decl

template<typename TPoint> // typename should be IPoint*<> type
struct IScene_Renderer
{
    using Point      = TPoint;
    using Points     = std::vector<Point>;
    using Value_Type = Point::Value_Type;

    virtual void draw_point(Point point, const IMaterial &material)                                                                                                   = 0; // точка
    virtual void draw_line(Point p1, Point p2, const IMaterial &material)                                                                                             = 0; // линия
    virtual void draw_polyline(const Points &points, const IMaterial &material)                                                                                       = 0; // полилиния
    virtual void draw_arc(Point center, Value_Type start_angle, Value_Type open_angle, const IMaterial &material)                                                     = 0; // дуга
    virtual void draw_bezier_curve(const Points &points, const IMaterial &material)                                                                                   = 0; // кривая безье
    virtual void draw_circle(Point center, Value_Type radius, const IMaterial &material)                                                                              = 0; // окружность
    virtual void draw_circle_sector(Point center, Value_Type start_angle, Value_Type open_angle, const IMaterial &material)                                           = 0; // сектор круга
    virtual void draw_ring(Point center, Value_Type radius, Value_Type inner_radius, const IMaterial &material)                                                       = 0; // кольцо
    virtual void draw_ring_sector(Point center, Value_Type radius, Value_Type inner_radius, Value_Type start_angle, Value_Type open_angle, const IMaterial &material) = 0; // сектор кольца
    virtual void draw_rectangle(Point pos_from, Point pos_to, const IMaterial &material)                                                                              = 0; // прямоугольник
    virtual void draw_fan_landfill(const Points &points, const IMaterial &material)                                                                                   = 0; // веерный полигон
    virtual void draw_lane_landfill(const Points &points, const IMaterial &material)                                                                                  = 0; // полосный полигон
    virtual void draw_ellipse(Point center, Value_Type radius_1, Value_Type radius_2, const IMaterial &material)                                                      = 0; // эллипс
    virtual void draw_horizontal_text(Point position, Value_Type angle, std::string_view text, const IMaterial &material)                                             = 0; // горизонтальный тексе
    virtual void draw_vertical_text(Point position, Value_Type angle, std::string_view text, const IMaterial &material)                                               = 0; // вертикальный текст
    virtual void draw_symbol(Point position, const IImage &image, const IMaterial &material)                                                                          = 0; // символ
    virtual void draw_video(Point position, const IVideo &video, const IMaterial &material)                                                                           = 0; // видео

    virtual void clear()                             = 0;
    virtual void clear(Point pos_from, Point pos_to) = 0;

    virtual void render() = 0;

    virtual ~IScene_Renderer() = 0;
};

using IScene_Renderer_2d32 = IScene_Renderer<IPoint2d<float>>;
using IScene_Renderer_2d64 = IScene_Renderer<IPoint2d<double>>;

} // namespace drawapi
