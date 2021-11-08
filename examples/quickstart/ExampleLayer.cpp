/*
 * @Author: ImGili
 * @Description: 
 */
#include"ExampleLayer.h"

#include<imgui.h>
#include<iostream>
void ExampleLayer::OnImGuiRender()
{
    ImGui::Begin("test");

    ImGui::End();
}


ExampleLayer::ExampleLayer()
    : Layer("ExampleLayer")
{}
ExampleLayer::~ExampleLayer()
{

}