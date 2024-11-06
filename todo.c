#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <leif/leif.h>

#define WIN_MARGIN 20.0f

//assaging window size
static int winw = 1280, winh = 720 ;
static LfFont titlefont;

int main(){
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(winw, winh, "Todo-App", NULL, NULL); //creating a window
    glfwMakeContextCurrent(window);

    lf_init_glfw(winw, winh, window); // frame size in leif

    LfTheme theme = lf_get_theme();
    theme.div_props.color = LF_NO_COLOR;
    lf_set_theme(theme);

    titlefont = lf_load_font("./fonts/inter-bold.ttf", 35.0f); //loading font

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0); //adding colour to the background

        lf_begin();
        lf_div_begin(((vec2s){WIN_MARGIN, WIN_MARGIN}), ((vec2s){winw - WIN_MARGIN * 2.0f, winh - WIN_MARGIN * 2.0f}),true); // setting margin

        lf_push_font(&titlefont);
        lf_text("Todo-App");
        lf_pop_font();


        //Button to add task style and content

        {   
            const float width =140.0f;

            lf_set_ptr_x_absolute(winw - width -WIN_MARGIN * 3.0f);
            LfUIElementProps props = lf_get_theme().button_props;
            props.margin_left = 0.0f;
            props.margin_right = 0.0f;
            props.color = (LfColor){65,167,204,255};
            props.border_width = 0.0f;
            props.corner_radius = 4.0f;
            lf_push_style_props(props);
            lf_set_line_should_overflow(false);
            lf_button_fixed("Add Task", width,-1);
            lf_set_line_should_overflow(true);
            lf_pop_style_props();
        }








        lf_div_end();
        lf_end();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    lf_free_font(&titlefont);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}