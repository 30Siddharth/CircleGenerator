#ifndef __MIN_CIRCLE_H__
#define __MIN_CIRCLE_H__

#include <wx/wx.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
class min_circle:public wxFrame
{
    public:
        min_circle()
        {
        
        }
        
        ~min_circle()
        {

        }
        // Function to compute the best fit circle using min squared error solution (SVD)
        bool solveMinCircle(const std::vector<Eigen::Vector2d> &points, float &midpointX, float &midpointY, double &radius)
        {
            int length = points.size();
           

            Eigen::MatrixXd ATranspose(3, length);
            Eigen::MatrixXd A(length, 3);
            Eigen::VectorXd AFirstCol(length);
            Eigen::VectorXd ASecCol(length);
            Eigen::VectorXd AFirstSquared(length);
            Eigen::VectorXd ASecSquared(length);
        
            Eigen::VectorXd b(length);
            Eigen::VectorXd soln(3);
            bool ok = true;

            if (length > 2)
            {
                for (int i = 0; i < length; i++)
                {
                    ATranspose(0, i) = points[i](0);
                    ATranspose(1, i) = points[i](1);
                    ATranspose(2, i) = 1;
                }

                A = ATranspose.transpose();

                for (int i = 0; i < length; i++)
                {
                    AFirstCol(i) = A(i, 0);
                    ASecCol(i) = A(i, 1);
                }

                for (int i = 0; i < length; i++)
                {
                    AFirstSquared(i) = AFirstCol(i) * AFirstCol(i);
                    ASecSquared(i) = ASecCol(i) * ASecCol(i);
                }

                b = AFirstSquared + ASecSquared;

                soln = A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);

                int s1 = soln(0);
                midpointX = s1 * 0.5;
                
                int s2 = soln(1);
                midpointY = s2 * 0.5;
                
                int s3 = soln(2);
                radius = sqrt((s1 * s1 + s2 * s2) / 4 + s3);
                return EXIT_SUCCESS;
            }
            else
            {
                return EXIT_FAILURE;
            }
            
            return EXIT_FAILURE;    
        }
};

# endif