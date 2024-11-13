#include "MyForm.h"

#include <Windows.h>
#include <vcclr.h>
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

public ref class DrawingForm : public Form
{
private:
    PictureBox^ pictureBox;
    Button^ lineButton;
    Button^ rectangleButton;
    Button^ ellipseButton;
    Button^ pieButton;
    Button^ fillButton;
    ColorDialog^ colorDialog;

    Color currentColor;
    bool isFilling;

public:
    DrawingForm()
    {
        this->Text = "Drawing Program";
        this->Size = Drawing::Size(800, 600);

        pictureBox = gcnew PictureBox();
        pictureBox->Dock = DockStyle::Fill;
        pictureBox->BackColor = Color::White;
        this->Controls->Add(pictureBox);

        lineButton = CreateButton("Line", 10);
        rectangleButton = CreateButton("Rectangle", 90);
        ellipseButton = CreateButton("Ellipse", 170);
        pieButton = CreateButton("Pie", 250);
        fillButton = CreateButton("Fill", 330);

        colorDialog = gcnew ColorDialog();
        currentColor = Color::Black;
        isFilling = false;

        pictureBox->Paint += gcnew PaintEventHandler(this, &DrawingForm::PictureBox_Paint);
    }

private:
    Button^ CreateButton(String^ text, int x)
    {
        Button^ button = gcnew Button();
        button->Text = text;
        button->Location = Point(x, 10);
        button->Click += gcnew EventHandler(this, &DrawingForm::Button_Click);
        this->Controls->Add(button);
        return button;
    }

    void Button_Click(Object^ sender, EventArgs^ e)
    {
        Button^ clickedButton = safe_cast<Button^>(sender);

        if (clickedButton == fillButton)
        {
            isFilling = !isFilling;
            fillButton->Text = isFilling ? "Outline" : "Fill";
        }
        else if (colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            currentColor = colorDialog->Color;
            DrawShape(clickedButton);
        }
    }

    void DrawShape(Button^ button)
    {
        Graphics^ g = pictureBox->CreateGraphics();
        Pen^ pen = gcnew Pen(currentColor, 2);
        SolidBrush^ brush = gcnew SolidBrush(currentColor);

        int width = pictureBox->Width / 2;
        int height = pictureBox->Height / 2;
        int x = (pictureBox->Width - width) / 2;
        int y = (pictureBox->Height - height) / 2;

        if (button == lineButton)
        {
            g->DrawLine(pen, x, y, x + width, y + height);
        }
        else if (button == rectangleButton)
        {
            if (isFilling)
                g->FillRectangle(brush, x, y, width, height);
            else
                g->DrawRectangle(pen, x, y, width, height);
        }
        else if (button == ellipseButton)
        {
            if (isFilling)
                g->FillEllipse(brush, x, y, width, height);
            else
                g->DrawEllipse(pen, x, y, width, height);
        }
        else if (button == pieButton)
        {
            if (isFilling)
                g->FillPie(brush, x, y, width, height, 0, 45);
            else
                g->DrawPie(pen, x, y, width, height, 0, 45);
        }

        delete pen;
        delete brush;
        delete g;
    }

    void PictureBox_Paint(Object^ sender, PaintEventArgs^ e)
    {
        // Цей метод викликається при необхідності перемалювати PictureBox
        // Тут можна додати код для відновлення всіх намальованих фігур
    }
};

[STAThread]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew DrawingForm());
    return 0;
}
