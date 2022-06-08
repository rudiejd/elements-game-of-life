/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License (https://opensource.org/licenses/MIT)
=============================================================================*/
#include <elements.hpp>

using namespace cycfi::elements;
using namespace std::chrono_literals;

constexpr auto fps = 1000ms / 60;
int step = 0;

// Main window background color
auto constexpr bkd_color = rgba(35, 35, 37, 255);
auto background = box(bkd_color);
auto alive = colors::red;
auto dead = colors::white;

auto make_cell() {


    auto&& draw =
            [=](context const& ctx, point val)
            {
                auto& cnv = ctx.canvas;
                cnv.begin_path();
                cnv.round_rect(ctx.bounds, get_theme().frame_corner_radius);
                cnv.fill_style(color(val.x, 0.0, 1.0).level(val.y));
                cnv.fill();
            };
    auto =
}
struct basic_row : htile_composite
{
    basic_row(size_t index)
            : htile_composite()
            , _index(index)
    {
        for (size_t i = 0; i < 10; i++)
        {
            auto input = margin(
                        {10, 10, 10, 10},
                        dead);
            push_back(share(input));
        }
    }

    size_t _index;
};

void animate(view& view_, std::vector<element_ptr>& ptr_list)
{
    step++;
    view_.refresh();
}


int main(int argc, char* argv[])
{
    app _app(argc, argv, "Active Dynamic List", "com.cycfi.active-dynamic-list");
    window _win(_app.name());
    _win.on_close = [&_app]() { _app.stop(); };

    view view_(_win);

    size_t list_size = 100;

    std::vector<element_ptr> ptr_list;
    ptr_list.resize(list_size, nullptr);
    auto && make_row = [&](size_t index)
    {
        if (ptr_list[index].get() == nullptr)
            ptr_list[index] = share(basic_row(index));
        return ptr_list[index];
    };


    auto cp = basic_vertical_cell_composer(list_size, make_row);
    auto content = vdynamic_list(cp);
    auto linked = link(content);

    auto b1 = icon_button(icons::minus, 1);
    auto b2 = icon_button(icons::plus, 1);

    b1.on_click = [&](bool)
    {
        std::cout << "dn " << std::endl;
        if (list_size <= 50)
            return;
        list_size -= 50;
        ptr_list.resize(list_size);
        content.resize(list_size);
        view_.refresh();
    };

    b2.on_click = [&](bool)
    {
        std::cout << "up " << std::endl;
        list_size +=50;
        ptr_list.resize(list_size);
        content.resize(list_size);
        view_.refresh();
    };

    view_.content(
            margin({10, 10, 10, 10},
                   vtile(
                           vscroller(hold(share(linked))),
                           htile(b1, b2)
                   )
            ),
            background
    );


    view_.post(fps, [&]() { animate(view_, ptr_list); });
    _app.run();
    return 0;
}
