#pragma once
#include "opengl.hpp"
#include "timer.hpp"
#include "MethodsDef.h"

extern int frame;
extern Timer sim_timer;
extern Timer obstacles_timer;
extern Timer get_constraint_timer;
extern Timer physics_step_timer;
extern Timer plasticity_step_timer;
extern Timer strainlimitng_step_timer;
extern Timer collision_step_timer;
extern Timer remeshing_step_timer;

extern Timer replay_timer;
extern Timer load_clothes_timer;
extern Timer replay_obstacles_timer;

void initImgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL2_Init();
}

void cleanImgui()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}

void display_ui()
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    ImGui::Begin("arcsim fps");

    //一个frame有多个step，但是还是step一次，渲染一次
    if (ImGui::CollapsingHeader("Simulate Info"))
    {
        ImGui::Text("single step time:%.3f s", sim.step_time);
        //ImGui::Text("frame steps:%d", sim.frame_steps);
        ImGui::Text("end_time:%.1f s", sim.end_time);
        ImGui::Separator();
    }

#ifdef REPLAY
    ImGui::Text("current frame:%d", sim.frame);
    ImGui::Text("current simulate time:%.3f s", sim.time);
    ImGui::Separator();

    ImGui::Text("single step FPS:%.1f ms/frame (%.1f FPS)", replay_timer.last * 1000, 1.0 / replay_timer.last);
    ImGui::BulletText("load clothes:%.1f ms", load_clothes_timer.last * 1000);
    ImGui::BulletText("obstacles animotion:%.1f ms", replay_obstacles_timer.last * 1000);

#else
    ImGui::Text("current frame:%d", sim.step);
    ImGui::Text("current simulate time:%.3f s", sim.time);
    ImGui::Separator();

    ImGui::Text("single step FPS:%.1f ms/frame (%.1f FPS)", sim_timer.last*1000,1.0/ sim_timer.last);
    ImGui::BulletText("obstacles animotion:%.1f ms", obstacles_timer.last * 1000);
    ImGui::BulletText("get constraint:%.1f ms", get_constraint_timer.last * 1000);
    ImGui::BulletText("physics step:%.1f ms", physics_step_timer.last * 1000);
    ImGui::BulletText("plasticity step:%.1f ms", plasticity_step_timer.last * 1000);
    ImGui::BulletText("strainlimitng step:%.3f ms", strainlimitng_step_timer.last * 1000);
    ImGui::BulletText("collision step:%.1f ms", collision_step_timer.last * 1000);
    ImGui::BulletText("remeshing step:%.1f ms", remeshing_step_timer.last * 1000);


#endif // SIMULATE

    ImGui::Separator();
    ImGui::Text("Imgui Estimate FPS %.1f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


    ImGui::End();

    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    glutSwapBuffers();
    glutPostRedisplay();
}