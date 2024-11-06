#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <leif/leif.h>



typedef enum{
    ALL = 0,
    PENDING,
    COMPLETED,
} entry_filter;

typedef struct{
    char* title;
    char* description *date; 
    bool completed;
}  task_entry;

#define WIN_MARGIN 20.0f

//assaging window size
static int winw = 1280, winh = 720 ;
//adding text
static LfFont titlefont;
static entry_filter current_filter ;
static task_entry* entries[1024];
static uint32_t numentries = 0;



//topbar
static void Topbar(){

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


}


// funtion of categorize the tasks
static void categorize(){   
            const uint32_t filter_count = 3;
            static const char* filter_options[] = {"All", "Pending", "Completed"};


            LfUIElementProps props = lf_get_theme().text_props;
            props.margin_top = 15.0f;
            props.margin_left = 10.0f;
            props.margin_right = 10.0f;
            props.padding = 10.0f;
            props.border_width = 0.0f;
            props.corner_radius = 8.0f;
            props.color = LF_NO_COLOR;
            props.text_color = LF_WHITE;   


            float width = 0.0f;
            float ptrx_before = lf_get_ptr_x();
            float ptry_before = lf_get_ptr_y();
            lf_push_style_props(props);
            lf_set_no_render(true);
            lf_set_ptr_y_absolute (lf_get_ptr_y() +30.0f);

            for(uint32_t i =0; i< filter_count; i++){
                lf_button(filter_options[i]);
            }
            lf_set_no_render(false);
            lf_set_ptr_y_absolute(ptry_before);

            width = lf_get_ptr_x() - ptrx_before - props.margin_right - props.padding;
            
            lf_set_ptr_x_absolute(winw - width - WIN_MARGIN * 3.0f);

            lf_set_line_should_overflow(false);
            for(uint32_t i =0; i< filter_count; i++){
            props.color = (current_filter == i) ? (LfColor){65,167,204,255} : LF_NO_COLOR; // colour of tag
            lf_push_style_props(props);
            if(lf_button(filter_options[i]) == LF_CLICKED) {
                current_filter = (entry_filter)i;
            }
            lf_pop_style_props();

            }
            lf_set_line_should_overflow(true);
        }





//main function
int main(){
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(winw, winh, "Todo-App", NULL, NULL); //creating a window
    glfwMakeContextCurrent(window);

    lf_init_glfw(winw, winh, window); // frame size in leif

    LfTheme theme = lf_get_theme();
    theme.div_props.color = LF_NO_COLOR;
    lf_set_theme(theme);

    titlefont = lf_load_font("./fonts/inter-bold.ttf", 35.0f); //loading font

    task_entry* entry = (task_entry*)malloc(sizeof(*entry));
    entry->completed = false;
    entry->date = "nothing";
    entry->description = "New doc in C";
    entry->title = "C project"
    entries[numentries++] = entries ;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0); //adding colour to the background

        lf_begin();
        lf_div_begin(((vec2s){WIN_MARGIN, WIN_MARGIN}), ((vec2s){winw - WIN_MARGIN * 2.0f, winh - WIN_MARGIN * 2.0f}),true); // setting margin


        Topbar();

        lf_next_line();

        categorize();
            //todo next
        {
            lf_div_begin(((vec2s){0.0f, 0.0f}), ((vec2s){winw - WIN_MARGIN * 2.0f, winh - WIN_MARGIN * 2.0f}), true);
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