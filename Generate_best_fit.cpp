#include <wx/wx.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "Eigen/Dense"
#include "Eigen/StdVector"
#include "minCircle.h"

#define BUTTON_BASE_ID 1
#define FIELDWIDTH 20
#define FIELDHEIGHT 20
#define WINDOWSIZE 900
#define GRIDDOTSIZE 10
#define PIXTODOTS 40
#define STARTDOT 75
#define STARTDOTCENTER STARTDOT+GRIDDOTSIZE/2

using namespace std;
class MainWindow : public wxFrame
{
public:
    // Constructor to create the Main Window for the application.
    MainWindow(const wxString &title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(WINDOWSIZE, WINDOWSIZE))
    {
        Centre();
        wxPanel *panel = new wxPanel(this, wxID_ANY);
        generate = new wxButton(this, 10000, "Generate", wxPoint(10, 10), wxSize(100, 50));

     
    }
    // Function to Draw the Grid
    void drawGridInit()
    {
        wxClientDC grid_init(this);
        wxPoint origin = grid_init.GetDeviceOrigin();
        grid_init.SetDeviceOrigin(origin.x, origin.y);
        wxPen penG(*wxLIGHT_GREY, 1);
        grid_init.SetPen(penG);
        grid_init.SetBrush(wxBrush(*wxLIGHT_GREY));

        for (int x = 0; x < FIELDWIDTH; x++)
        {
            for (int y = 0; y < FIELDHEIGHT; y++)
            {        
                grid_init.DrawRectangle(STARTDOT + x * PIXTODOTS, STARTDOT + y * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);   
            }
        }
        //intialize grid points to 0
        for (int x = 0; x < FIELDWIDTH; x++)
        {
            for (int y = 0; y < FIELDHEIGHT; y++)
            {
                state_btn[x * FIELDWIDTH + y] = 0;
            }
        }
        grid_init.SetPen(wxNullPen);
        grid_init.SetBrush(wxNullBrush);
    }
    

    //invoked when generate is clicked
    void onGenerate(wxCommandEvent &evt)
    {
        wxClientDC circle(this);
        wxPen penB(*wxBLUE, 1); 
        
        // Push all points selected into the buffer.
        for (int x = 0; x < FIELDWIDTH; x++)
        {
            for (int y = 0; y < FIELDHEIGHT; y++)
            {
                if (state_btn[x * FIELDWIDTH + y] == 1)
                {
                    samplePoints.push_back(Eigen::Vector2d(round(x * PIXTODOTS + STARTDOTCENTER), round(y * PIXTODOTS + STARTDOTCENTER)));
                    state_btn[x * FIELDWIDTH + y] = 0;
                }
            }
        }

        float xc, yc;
        double radius;

        // invoke minCircle function to generate the center and radius of the circle
        min_circle *minCircle= new min_circle();
        if(minCircle->solveMinCircle(samplePoints, xc, yc, radius))
            drawGridInit();
        // Draw the Circle
        else
        {
                    
            wxPoint origin = circle.GetDeviceOrigin();
            circle.SetDeviceOrigin(origin.x, origin.y);
            circle.SetBrush(wxBrush(wxTransparentColour, wxTRANSPARENT));
            circle.SetPen(penB);
            circle.DrawCircle(xc, yc, radius);
            circle.SetPen(wxNullPen);

            cout << xc << " " << yc << " " << radius << endl;
        }
            grid_init = 1;
            generate_state = 1;
            samplePoints.clear();
        
        evt.Skip();
    }

    //invoked by mouse operations
    void onMouseClick(wxMouseEvent &event)
    {
        int x, y;
        
        wxClientDC point(this);
        wxPoint origin = point.GetDeviceOrigin();
        wxPen penB(*wxBLUE, 1);
        wxPen penG(*wxLIGHT_GREY, 1);
        point.SetDeviceOrigin(origin.x, origin.y);

        if (grid_init == 0)
        {
            drawGridInit();
            grid_init = 1;
        }

        if (event.ButtonUp())
        {

            //if generate_state is 1 we have generated the circle and we refresh the grid
            if (generate_state == 1)
            {

                Refresh();
                generate_state = 0;
                grid_init = 0;
                drawGridInit();    
            }
            //invoked when generate state is 0 we are selecting and deselecting points
            else
            {
                wxPoint pt1=wxGetMousePosition();
                x = floor((pt1.x - this->GetScreenPosition().x - STARTDOTCENTER) /(float) (PIXTODOTS));
                y = floor((pt1.y - this->GetScreenPosition().y - STARTDOTCENTER) /(float) (PIXTODOTS));
                
                // Handle button clickes outside grid
                if(!(x>=FIELDWIDTH || x< 0 || y>=FIELDHEIGHT || y <0))
                {
                     
                    // if else block is for toggling the grid points
                    if (state_btn[x * FIELDWIDTH + y] == 0)
                    {

                    
                        point.SetPen(penB);
                        point.SetBrush(wxBrush(*wxBLUE));
                        point.DrawRectangle(STARTDOT + x * PIXTODOTS, STARTDOT + y * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);
                        point.SetPen(wxNullPen);
                        point.SetBrush(wxNullBrush);
                        state_btn[x * FIELDWIDTH + y] = 1;
                    
                    }
                    else
                    {
                    
                        point.SetPen(penG);
                        point.SetBrush(wxBrush(*wxLIGHT_GREY));
                        point.DrawRectangle(STARTDOT + x * PIXTODOTS, STARTDOT + y * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);
                        point.SetPen(wxNullPen);
                        point.SetBrush(wxNullBrush);
                        state_btn[x * FIELDWIDTH + y] = 0;
                    
                    }
                }
            }
        }
       
    }

public:
  
    wxButton *generate = nullptr;
    bool state_btn[FIELDHEIGHT * FIELDWIDTH];
  
    // Event handle declare
    wxDECLARE_EVENT_TABLE();
    bool grid_init = 0;
    bool generate_state = 0;
    std::vector<Eigen::Vector2d> samplePoints;
};
// Event handling table
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MOUSE_EVENTS(MainWindow::onMouseClick)
    EVT_BUTTON(10000, MainWindow::onGenerate)
wxEND_EVENT_TABLE()

class MyApp : public wxApp
{
public:
    bool OnInit()
    {
        MainWindow *Window = new MainWindow(wxT("Circle Generator"));

        Window->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);