#include "mtm.h"

mtm::mtm()
{

}

mtm::~mtm()
{

}
// patern and window should be cv_64F
// Algorithm 1 In the paper
int mtm::PWCp2w (cv::Mat patern,cv::Mat window,std::vector<int> steps,cv::Mat &output )
 {


    //the size of the output in this case is different
    if (patern.channels()>1 || window.channels()>1)
    {
        return -1;
    }

    //todo
    // there are 2 posible implementations here; that in matlab are solved with the function conv2(im,blockFilter,'valid '); this means that
    // only takes the value of the valid windows, this means that all the paters that are into the windows with any pixel outside
    // so to make this more fast( when patern and window are the same) we can reduce the convolutions to 1.
    //for example to calculate w1 and w2 is only cv::sum(window) and cv::sum(window^2)

     cv::Mat kernel = cv::Mat::ones(patern.size(),CV_64F);
     float m = (float)patern.cols * patern.rows;

     cv::Mat W1;
     cv::Mat W2;
     //windows sum
     cv::Point anchor(kernel.cols - kernel.cols/2 - 1, kernel.rows - kernel.rows/2 - 1);
     cv::filter2D(window,W1,-1,kernel,anchor,0,cv::BORDER_CONSTANT);
     W1 = W1.colRange((kernel.cols-1)/2, W1.cols - kernel.cols/2).rowRange((kernel.rows-1)/2, W1.rows - kernel.rows/2);
     cv::Mat window_2 ;
     cv::pow(window,2,window_2);
     // windows sum of square
     cv::filter2D(window_2,W2,-1,kernel,anchor,0,cv::BORDER_CONSTANT);
     W2 = W2.colRange((kernel.cols-1)/2, W2.cols - kernel.cols/2).rowRange((kernel.rows-1)/2, W2.rows - kernel.rows/2);

     // calculate denominator
     cv::Mat W1_2;
     cv::pow(W1,2,W1_2);
     cv::Mat aux,D2;
     cv::divide(m,W1_2,aux);
     //aux = W1_2/m;
     cv::subtract(W2,aux,D2);
// the limts to changue to 0 should be epsilon, to have the same result than matlab
 //double limits = std::numeric_limits<double>::epsilon();
     double limits = 0.001;
     // look into all the values that are 0
     for(int y=0;y<D2.rows;y++)
     {
         for(int x=0;x<D2.cols;x++)
         {
             // get pixel
             double color = D2.at<double>(y,x);
             // if is 0 chague to 1
             if (color<limits)  D2.at<double>(y,x)=1.0;
         }
     }


     cv::Mat D1 = cv::Mat::zeros(D2.size(),CV_64F);
     for ( int j=0;j<steps.size()-1;j++)
     {
         cv::Mat slice = cv::Mat::zeros(patern.size(),CV_64F);
         //calculate the slice for each interval of values
         for(int y=0;y<patern.rows;y++)
         {
             for(int x=0;x<patern.cols;x++)
             {
                double value = patern.at<double>(cv::Point(x,y));
                if (value >= steps[j] && value < steps[j+1])slice.at<double>(cv::Point(x,y))=1.0;

             }
         }
         // because i have no dimensions, if i have dimensions is sum(slice)[0]
        double sum = cv::sum(slice)[0];
         if (sum==0)sum=1;
         cv::Mat fliped_slice;
         //check the flip
         //cv::flip(slice,fliped_slice,-1);
         //rotate 180 degrees
         // the convolution in opencv flips automatically ,then in matlab is necesary but in opencv not
          slice.copyTo(fliped_slice);
          //fliped_slice = slice;
         // cv::transpose(slice,fliped_slice);
//         cv::transpose(slice,fliped_slice);
//         cv::flip(fliped_slice,fliped_slice,1);
//         cv::transpose(fliped_slice,fliped_slice);
//         cv::flip(fliped_slice,fliped_slice,1);

         cv::Mat T,T_2,aux2;
          cv::Point anchor(fliped_slice.cols - fliped_slice.cols/2 - 1, fliped_slice.rows - fliped_slice.rows/2 - 1);

         cv::filter2D(window,T,-1,fliped_slice,anchor,0,cv::BORDER_CONSTANT);

          T = T.colRange((fliped_slice.cols-1)/2, T.cols - fliped_slice.cols/2).rowRange((fliped_slice.rows-1)/2, T.rows - fliped_slice.rows/2);

          cv::pow(T,2,T_2);
          //  aux2=T_2/sum;
         cv::divide(sum,T_2,aux2);
         cv::add(D1,aux2,D1);
     }

     cv::Mat aux3;
     cv::Mat aux4;
     cv::pow(W1,2,aux3);
     cv::subtract(W2,aux3,aux4);
     cv::divide(1.0/m,aux3,aux4);
   //  aux4=aux3/(patern.rows*patern.cols);
     aux4.copyTo(output);
     output= aux4;
    return 0;
 }
// patern and window should be cv_64F
// Algorithm 2 In the paper

int mtm::PWCw2p(cv::Mat patern,cv::Mat window,std::vector<int> steps,cv::Mat &output )
{
    if (patern.channels()>1 || window.channels()>1)
    {
        return -1;
    }

    cv::Mat kernel = cv::Mat::ones(patern.size(),CV_64F);
    double p1,p2,d2;
    cv::Mat patern_2;
    p1= cv::sum(patern)[0];
    cv::pow(patern,2,patern_2);
    p2 = cv::sum(patern_2)[0];
    d2= p2-(p1*p1)/(patern.cols*patern.rows);
    // d2 can not be 0;
    if (d2<0.0001) d2=1;
    cv::Size aux;
    aux=window.size()-patern.size();
    aux.height=aux.height+1;
    aux.width=aux.width+1;
    cv::Mat D1 = cv::Mat::zeros(aux,CV_64F);
    for ( int j=0;j<steps.size()-1;j++)
    {
        cv::Mat slice = cv::Mat::zeros(window.size(),CV_64F);
        //calculate the slice for each interval of values
        for(int y=0;y<window.rows;y++)
        {
            for(int x=0;x<window.cols;x++)
            {
               double value = window.at<double>(cv::Point(x,y));
               if (value >= steps[j] && value < steps[j+1])slice.at<double>(cv::Point(x,y))=1.0;

            }
        }


        cv::Mat Nj,T,T_2,T_aux;
        cv::Point anchor(kernel.cols - kernel.cols/2 - 1, kernel.rows - kernel.rows/2 - 1);

       cv::filter2D(slice,Nj,-1,kernel,anchor,0,cv::BORDER_CONSTANT);

        Nj = Nj.colRange((kernel.cols-1)/2, Nj.cols - kernel.cols/2).rowRange((kernel.rows-1)/2, Nj.rows - kernel.rows/2);
        for(int y=0;y<Nj.rows;y++)
        {
            for(int x=0;x<Nj.cols;x++)
            {
               double value = Nj.at<double>(cv::Point(x,y));
               if (value == 0.0)Nj.at<double>(cv::Point(x,y))=1.0;
            }
        }

        cv::Point anchor2(patern.cols - patern.cols/2 - 1, patern.rows - patern.rows/2 - 1);

       cv::filter2D(slice,T,-1,patern,anchor2,0,cv::BORDER_CONSTANT);

        T = T.colRange((patern.cols-1)/2, T.cols - patern.cols/2).rowRange((patern.rows-1)/2, T.rows - patern.rows/2);

        cv::pow(T,2,T_2);
        T_aux=T_2/Nj;
        cv::add(D1,T_aux,D1);
    }
    cv::Mat aux3;
    cv::Mat aux4;
    cv::subtract(p2,D1,aux3);
    aux4=aux3/d2;
  //  cv::divide(aux3,D2,aux4);

    output= aux4;
    return 0;

}

int mtm::PWCmax(cv::Mat patern,cv::Mat window,std::vector<int> steps,cv::Mat &output )
{
    cv::Mat output1, output2;
    cv::Size prueba;
    //todo

    //insert here exception control
    int aux =PWCp2w(patern,window,steps,output1);
    if (aux==-1)return -1;
    aux= PWCw2p(patern,window,steps,output2);
    if (aux==-1)return -1;

    if (output1.size().height>output1.size().height)prueba.height=output1.size().height;
    else prueba.height=output2.size().height;
    if (output1.size().width>output1.size().width)prueba.width=output1.size().width;
    else prueba.width=output2.size().width;

    output = cv::Mat::zeros(prueba,CV_64F);
    for(int y=0;y<output2.rows;y++)
    {
        for(int x=0;x<output2.cols;x++)
        {
           double value = output2.at<double>(cv::Point(x,y));
           double value2= output1.at<double>(cv::Point(x,y));
           if (value >=value2) output.at<double>(cv::Point(x,y))=value;
           else output.at<double>(cv::Point(x,y))=value2;
        }
    }
    return 0;
}


int mtm::PWLp2w (cv::Mat patern,cv::Mat window,std::vector<int> steps,cv::Mat &output )
 {

  //   cv::Mat Sum = cv::Mat::zeros((window.rows-patern.rows)+1,(window.cols-patern.cols)+1,CV_64F);
     std::vector<cv::Mat> slice,slice_bar,slice_rel;
     //initialize slice
     cv::Mat meter= cv::Mat::zeros(patern.rows,patern.cols,CV_64F);
     //create patern slices
     for (int i=0;i<steps.size();i++)slice_bar.push_back(meter);
     for (int j=0;j<steps.size()-1;j++)
     {
         cv::Mat inputslice = cv::Mat::zeros(patern.size(),CV_64F);
         cv::Mat inputslice_rel = cv::Mat::zeros(patern.size(),CV_64F);
         //calculate the slice for each interval of values
         for(int y=0;y<patern.rows;y++)
         {
             for(int x=0;x<patern.cols;x++)
             {
                double value = patern.at<double>(cv::Point(x,y));
                if (value >= steps[j] && value < steps[j+1])inputslice.at<double>(cv::Point(x,y))=1.0;

             }
         }

        double div= steps[j+1]-steps[j];

         cv::Mat aux_rel= (patern-steps[j])/div;

       //  inputslice_rel= inputslice/aux_rel;
         cv::multiply(inputslice,aux_rel,inputslice_rel);
         slice.push_back(inputslice);
         slice_rel.push_back(inputslice_rel);
     }




     for (int j=1;j<steps.size()-1;j++)
     {
         cv::Mat test;
         test =slice[j]-slice_rel[j]+slice_rel[j-1];
         slice_bar[j]=test;

     }


     slice_bar[0]=slice[0]-slice_rel[0];
     slice_bar[steps.size()-1] = slice_rel[steps.size()-2];

     // calculate phi, psi and rho, in this case is more simple because is only one convolution
     //and for rho we need to make the convolution;
     //then...
     std::vector<cv::Mat> phi,psi,rho;

     for (int j=0;j<steps.size();j++)
     {
         cv::Mat input = cv::Mat::zeros(1,1,CV_64F);
          cv::Mat input2 = cv::Mat::zeros(1,1,CV_64F);

         cv::Mat aux_slice_bar;
         cv::pow(slice_bar[j],2,aux_slice_bar);
         input= cv::sum(aux_slice_bar)[0];
       // input.at<double>(cv::Point(0,0))=input_aux;

         phi.push_back(input);
         if (j<steps.size()-1)
         {
         cv::multiply(slice_bar[j],slice_bar[j+1],aux_slice_bar);
         input2= cv::sum(aux_slice_bar);
         psi.push_back(input2);
         }
         cv::Mat rho_aux;
         cv::Point anchor2(slice_bar[j].cols - slice_bar[j].cols/2 - 1, slice_bar[j].rows - slice_bar[j].rows/2 - 1);

        cv::filter2D(window,rho_aux,-1,slice_bar[j],anchor2,0,cv::BORDER_CONSTANT);

         rho_aux = rho_aux.colRange((slice_bar[j].cols-1)/2, rho_aux.cols - slice_bar[j].cols/2).rowRange((slice_bar[j].rows-1)/2, rho_aux.rows - slice_bar[j].rows/2);
         rho.push_back(rho_aux);
     }

     std::vector<cv::Mat> betha;

     TDMA(phi,psi,rho,betha);

     cv::Mat Sum ;
     for (int i=0;i<betha.size();i++)
     {

         cv::Mat temp_sum;
         cv::multiply(betha[i],rho[i],temp_sum);
         if (i==0)Sum = temp_sum;
         else  Sum = Sum+temp_sum;

     }

     cv::Mat kernel = cv::Mat::ones(patern.size(),CV_64F);
     cv::Mat W1;
     cv::Mat W2;
     //windows sum
     cv::Point anchor(kernel.cols - kernel.cols/2 - 1, kernel.rows - kernel.rows/2 - 1);
     cv::filter2D(window,W1,-1,kernel,anchor,0,cv::BORDER_CONSTANT);
     W1 = W1.colRange((kernel.cols-1)/2, W1.cols - kernel.cols/2).rowRange((kernel.rows-1)/2, W1.rows - kernel.rows/2);
     cv::Mat window_2 ;
     cv::pow(window,2,window_2);
     // windows sum of square
     cv::filter2D(window_2,W2,-1,kernel,anchor,0,cv::BORDER_CONSTANT);
     W2 = W2.colRange((kernel.cols-1)/2, W2.cols - kernel.cols/2).rowRange((kernel.rows-1)/2, W2.rows - kernel.rows/2);
     cv::Mat aux3,aux4,aux5;
     cv::pow(W1,2,aux3);
     double dividir= (patern.cols*patern.rows);
     aux4=aux3/dividir;
     cv::subtract(W2,aux4,aux5);


     for(int y=0;y<aux5.rows;y++)
     {
         for(int x=0;x<aux5.cols;x++)
         {
            double value = aux5.at<double>(cv::Point(x,y));
            if (value == 0.0)aux5.at<double>(cv::Point(x,y))=1.0;
         }
     }

     cv::Mat aux6= (W2-Sum);
     cv::divide(aux6,aux5,output);
     return 0;


 }


int mtm::PWLw2p(cv::Mat patern, cv::Mat window, std::vector<int> steps, cv::Mat &output)
{
    cv::Mat kernel = cv::Mat::ones(patern.size(),CV_64F);
    std::vector<cv::Mat> slice,slice_bar,slice_rel;
    //initialize slice
    cv::Mat meter= cv::Mat::zeros(window.rows,window.cols,CV_64F);
    //create patern slices
    for (int i=0;i<steps.size();i++)slice_bar.push_back(meter);
    for (int j=0;j<steps.size()-1;j++)
    {
        cv::Mat inputslice = cv::Mat::zeros(window.size(),CV_64F);
        cv::Mat inputslice_rel = cv::Mat::zeros(window.size(),CV_64F);
        //calculate the slice for each interval of values
        for(int y=0;y<window.rows;y++)
        {
            for(int x=0;x<window.cols;x++)
            {
               double value = window.at<double>(cv::Point(x,y));
               if (value >= steps[j] && value < steps[j+1])inputslice.at<double>(cv::Point(x,y))=1.0;

            }
        }
       double div= steps[j+1]-steps[j];

        cv::Mat aux_rel= (window-steps[j])/div;

      //  inputslice_rel= inputslice/aux_rel;
        cv::multiply(inputslice,aux_rel,inputslice_rel);
        slice.push_back(inputslice);
        slice_rel.push_back(inputslice_rel);
    }

    for (int j=1;j<steps.size()-1;j++)
    {
        cv::Mat test;
        test =slice[j]-slice_rel[j]+slice_rel[j-1];
        slice_bar[j]=test;

    }


    slice_bar[0]=slice[0]-slice_rel[0];
    slice_bar[steps.size()-1] = slice_rel[steps.size()-2];
    std::vector<cv::Mat> phi,psi,rho;

    for (int j=0;j<steps.size();j++)
    {
        cv::Mat input;
         cv::Mat input2;

        cv::Mat aux_slice_bar;
        cv::pow(slice_bar[j],2,aux_slice_bar);

        cv::Point anchor_phi(kernel.cols - kernel.cols/2 - 1, kernel.rows - kernel.rows/2 - 1);
        cv::filter2D(aux_slice_bar,input,-1,kernel,anchor_phi,0,cv::BORDER_CONSTANT);

        input = input.colRange((kernel.cols-1)/2, input.cols - kernel.cols/2).rowRange((kernel.rows-1)/2, input.rows - kernel.rows/2);
        phi.push_back(input);

        if (j<steps.size()-1)
        {
        cv::Mat aux_slice_bar_2;
        cv::multiply(slice_bar[j],slice_bar[j+1],aux_slice_bar_2);
        cv::Point anchor_psi(kernel.cols - kernel.cols/2 - 1, kernel.rows - kernel.rows/2 - 1);
        cv::filter2D(aux_slice_bar_2,input2,-1,kernel,anchor_psi,0,cv::BORDER_CONSTANT);
        input2 = input2.colRange((kernel.cols-1)/2, input2.cols - kernel.cols/2).rowRange((kernel.rows-1)/2, input2.rows - kernel.rows/2);
        psi.push_back(input2);
        }
        cv::Mat aux_slice_bar2;

        cv::flip(slice_bar[j],aux_slice_bar2,-1);
        cv::Mat patern_2;

        cv::flip(patern,patern_2,-1);
        cv::Mat rho_aux;
        cv::Point anchor2(patern_2.cols - patern_2.cols/2 - 1, patern_2.rows - patern_2.rows/2 - 1);

        cv::filter2D(aux_slice_bar2,rho_aux,-1,patern_2,anchor2,0,cv::BORDER_CONSTANT);

        rho_aux = rho_aux.colRange((patern_2.cols-1)/2, rho_aux.cols - patern_2.cols/2).rowRange((patern_2.rows-1)/2, rho_aux.rows - patern_2.rows/2);
        rho.push_back(rho_aux);
    }


    std::vector<cv::Mat> betha;

      TDMA(phi,psi,rho,betha);



      cv::Mat Sum ;
      for (int i =0;i<betha.size();i++)
      {

          cv::Mat temp_sum;
          cv::multiply(betha[i],rho[i],temp_sum);
          if (i==0)Sum = temp_sum;
          else  Sum = Sum+temp_sum;

      }




      double W1 = cv::sum(patern)[0];
      cv::Mat auxW2 ;
      cv::pow(patern,2,auxW2);
      double W2= cv::sum(auxW2)[0];


      double dividir= (patern.cols*patern.rows);
      double D2 = W2-(W1*W1)/dividir;
      if (D2==0.0)D2=1.0;


      cv::Mat aux2= (W2-Sum);
      cv::divide(aux2,D2,output);



      return 0;

}


 void mtm::TDMA  (std::vector<cv::Mat> phi,std::vector<cv::Mat> psi,std::vector<cv::Mat> rho,std::vector<cv::Mat> &betha)
 {
     //aux variables
     std::vector<cv::Mat> omega,sigma;
     cv::Mat tempphi, tempome, tempsig;

     tempphi = phi[0];
     std::vector<int> indices;
     //calculate omega
     for(int y=0;y<tempphi.rows;y++)
     {
         for(int x=0;x<tempphi.cols;x++)
         {

            double value = tempphi.at<double>(cv::Point(x,y));
            if (value ==0)
            {
                int indice= tempphi.rows*y+x;
                indices.push_back(indice);
                tempphi.at<double>(cv::Point(x,y))=1.0;
            }
     }
     }


     cv::divide(psi[0],tempphi,tempome);
   //  tempome= rho[0]/tempphi;



      for(int y=0;y<indices.size();y++)
      {
          int x= indices[y]%tempome.rows;
          int y_aux= indices[y]/tempome.rows;
          tempome.at<double>(cv::Point(x,y_aux))=0.0;

      }

      omega.push_back(tempome);
        //calculate sigma
      cv::divide(rho[0],tempphi,tempsig);
      // tempsig= phi[0]/tempphi;

       for(int y=0;y<indices.size();y++)
       {
           int x= indices[y]%tempsig.rows;
           int y_aux= indices[y]/tempsig.rows;
           tempsig.at<double>(cv::Point(x,y_aux))=0.0;

       }
       sigma.push_back(tempsig);

       //iterative calculation - forward computation
       //
       //
       //
       for (int i=1;i<phi.size()-1;i++)
       {

        cv::Mat temp,temp2,tempome2;
        cv::multiply(omega[i-1],psi[i-1],temp2);
        temp=   phi[i] - temp2;
        std::vector<int> indices_temp;
        //calculate omega
        for(int y=0;y<temp.rows;y++)
        {
            for(int x=0;x<temp.cols;x++)
            {

               double value = temp.at<double>(cv::Point(x,y));
               if (value ==0.0)
               {
                   int indice= temp.rows*y+x;
                   indices_temp.push_back(indice);
                   temp.at<double>(cv::Point(x,y))=1.0;
               }
        }
        }



        cv::divide(psi[i],temp,tempome2);
         //tempome = psi[i]/temp;
         for(int y=0;y<indices_temp.size();y++)
         {
             int x= indices_temp[y]%tempome2.rows;
             int y_aux= indices_temp[y]/tempome2.rows;
             tempome2.at<double>(cv::Point(x,y_aux))=0.0;

         }
         omega.push_back(tempome2);

         //tempsig = rho[i]-sigma[i-1]*psi[i-1]/temp;
         cv::Mat tempsig1,tempsig2,tempsig3;
         cv::multiply(sigma[i-1],psi[i-1],tempsig1);
           tempsig3=rho[i]-tempsig1;
         cv::divide(tempsig3,temp,tempsig2);


         for(int y=0;y<indices_temp.size();y++)
         {
             int x= indices_temp[y]%tempsig2.rows;
             int y_aux= indices_temp[y]/tempsig2.rows;
             tempsig2.at<double>(cv::Point(x,y_aux))=0.0;

         }
       sigma.push_back(tempsig2);

       }

       //after iteration

       cv::Mat temp,temp2,temp3,temp4;
        cv::multiply(omega[phi.size()-2],psi[phi.size()-2],temp2);
        cv::subtract(phi[phi.size()-1],temp2,temp);
       //temp=phi[phi.size()-1]-temp2;

       //cv::Mat temp=phi[phi.size()]-omega[phi.size()-1]*psi[phi.size()-1];
       std::vector<int> indices_temp;
       //calculate omega
       for(int y=0;y<temp.rows;y++)
       {
           for(int x=0;x<temp.cols;x++)
           {

              double value = temp.at<double>(cv::Point(x,y));
              if (value ==0)
              {
                  int indice= temp.rows*y+x;
                  indices_temp.push_back(indice);
                  temp.at<double>(cv::Point(x,y))=1.0;
              }
       }
       }

       cv::multiply(sigma[phi.size()-2],psi[phi.size()-2],temp4);
       cv::subtract(rho[phi.size()-1],temp4,temp3);
      // temp3=rho[phi.size()-1]-temp4;
       cv::Mat tempsigfinal;
       cv::divide(temp3,temp,tempsigfinal);
       //tempsig =(rho[phi.size()-1]-sigma[phi.size()-2]*psi[phi.size()-2])/temp;
        for(int y=0;y<indices_temp.size();y++)
        {
            int x= indices_temp[y]%tempsigfinal.rows;
            int y_aux= indices_temp[y]/tempsigfinal.rows;
            tempsigfinal.at<double>(cv::Point(x,y_aux))=0.0;

        }

        sigma.push_back(tempsigfinal);
       // back substitution, first initializate betha with the same values os sigma
        for (int i=0;i<sigma.size();i++){
            if(i==0)betha.push_back(cv::Mat::zeros(sigma[i].size(),CV_64F));
            else betha.push_back(sigma[i]);
}
        for (int i= (sigma.size()-2);i>=0;i--)
        {
            cv::Mat mulaux;
           // double omegaaaa = omega[i].at<double>(cv::Point(0,0));
            cv::multiply(omega[i],betha[i+1],mulaux);
            std::vector<double> ver;
          for(int y=0;y<mulaux.rows;y++)
          {
              for(int x=0;x<mulaux.cols;x++)
              {
                 double value = mulaux.at<double>(cv::Point(x,y));
                ver.push_back(value);

              }
          }

            //mulaux=betha[i+1]*omegaaaa;
            cv::subtract(sigma[i],mulaux,betha[i]);
          //  betha[i]= sigma[i]- mulaux;


        }



 }
