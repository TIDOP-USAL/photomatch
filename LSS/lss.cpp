#include "lss.h"




  int LSS::compute(const cv::Point& p, const cv::Mat& input,   cv::Mat_<float> &polar )
    {

        if( p.x-odim/2 < 0 || p.y-odim/2 < 0 || p.x+odim/2 >= input.cols || p.y+odim/2 >= input.rows)
        {

         }
        else{

        cv::Mat dos;
        input.copyTo(dos);
        cv::Mat ipatch = dos(cv::Range(p.y-idim/2,p.y+idim/2),cv::Range(p.x-idim/2, p.x+idim/2));
        cv::Mat opatch = dos(cv::Range(p.y-odim/2,p.y+odim/2),cv::Range(p.x-odim/2, p.x+odim/2));


        cv::Mat w;
        cv::Mat_<float> distance_surface( odim/idim, odim/idim );
        cv::Mat_<float> polar_;

        float epsilon, eta, corr, current;
        float* angle = new float[angle_steps];
        float* radii = new float[radii_steps];

        for (int i = 0 ; i < angle_steps ; ++i)
            angle[i] = i * 2. * CV_PI/angle_steps;
        for(int i  = 0 ; i < radii_steps ; ++i)
            radii[i] = i*(odim/2)/radii_steps;

        for(int i = 0, ii=0 ; i < odim ; i += idim, ++ii)
        {
            for(int j = 0, jj = 0 ; j < odim ; j += idim, ++jj)
            {
                w = opatch(cv::Range(i,i+idim),cv::Range(j,j+idim));
                distance_surface(ii,jj) = LSS::ssd(ipatch,w);
            }
        }

        //cv::normalize
        cv::normalize( distance_surface, distance_surface, 0., 1., cv::NORM_MINMAX );

        //log-polar
        int n, m;
        polar_ = cv::Mat_<float>::zeros( radii_steps, angle_steps );
        for(int i = 0 ; i < distance_surface.rows ; ++i)
        {
            for(int j = 0 ; j < distance_surface.cols ; ++j)
            {
                epsilon = sqrt( double(i*i+j*j) );
                if(i)
                    eta = atan( j/double(i) );
                else
                    eta = CV_PI/2.;

                n = 0; m = 0;
                while(radii[n++]<epsilon && n < radii_steps){}
                while(angle[m++]<eta && m < angle_steps){}
                --n;--m;
                corr = exp(-distance_surface(i,j)/(varnoise*.1));
                current = polar_(n,m);

                polar_(n,m) += corr;
            }
        }
        //mirar cuando es vacío
        //cv::normalize polar
        cv::normalize( polar_, polar_, 0., 1., cv::NORM_MINMAX );
        polar_.copyTo(polar);
        return 1;
    }
        return -1;
    }


    float LSS::ssd(  cv::Mat& a,  cv::Mat& b )
    {
        float c = 0;
        for(int i = 0 ; i<a.rows ; ++i)
            for(int j = 0 ; j<a.cols ; ++j)
            {

                float baux= b.at<float>(i,j);
                float aaux = a.at<float>(i,j);
                c += (aaux-baux) * (aaux-baux);
            }
        return c;
    }
