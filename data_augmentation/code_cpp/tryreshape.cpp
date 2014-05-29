#include"combined_augment_returnmat.cpp"
int main(int argc,char *argv[])
{   
    
    Mat img=imread(argv[1]);
    string a(argv[1]);
    Mat created=fn_image(img,a);
    cout<<created;
}

