#include <stdio.h>
#include <math.h>
#define er 5e-7
#define PI  3.14159265358979323


double polleg(int, double);                     //Avaluar polinomi de Legendre
double polcheb(int, double);                    //Avaluar polinomi de Chebyxhev
void intervalscheb(int, double [][2]);          //Trobar intervals on hi ha arrels
void intervalsleg(int, double [][2]);
void mig(int n, double [][2], double []);       //Fer el punt mig de tots els intervals
double newtonleg(double, int);                  //Mètode de Newton per Legendre
double newtonche(double, int);                  //Mètode de Newton per Chebyxhev
double derivada(double,int);                    
double aileg(int,double);                       //Coeficients ai de Legendre
double abs1(double);                            //Funcions a integrar (1 legendre 2 Chebyxhev)
double intabs1(int, double [],double []);       //Integral
double abs2(double);
double intabs2(int, double [],double []);
double exp1(double);
double intexp1(int, double [],double []);
double exp1(double);
double intexp2(int, double [],double []);
double trapezisabs(int);
double trapezisexp(int);

int main()
{
    int n;
    scanf("%d",&n);
    double inter[n][2];
    double arrels[n];
    double ai[n];
    
    intervalscheb(n, inter);                //Trobar intervals de Chebyxhev
    mig(n, inter, arrels);
    
    for(int i=0; i<n;i++)                   //Trobar arrels de Chebyxhev
    {
        arrels[i]=newtonche(arrels[i],n);
    }
    
    for(int i=0; i<n; i++)                  //Trobar coeficients de Chebyxhev
    {
        ai[i]=PI/n;
    }
    
    printf("Valor absolut Chebyxhev: %.16G\n", intabs2(n, arrels, ai));
    
    printf("Exponencial Chebyxhev: %.16G\n", intexp2(n, arrels, ai));
    
    intervalsleg(n, inter);                 //Trobar intervals de Legendre
    mig(n, inter, arrels);
    
    for(int i=0; i<n;i++)                   
    {
        arrels[i]=newtonleg(arrels[i],n);   //Trobar arrels de Legendre
    }
    
    for(int i=0; i<n; i++)
    {
        ai[i]=aileg(n, arrels[i]);          //Trobar coeficients de Legendre
    }
    
    printf("Valor absolut Legendre: %.16G\n", intabs1(n, arrels, ai));
    
    printf("Exponencial Legendre: %.16G\n", intexp1(n, arrels, ai));
    
    printf("Valor absolut %d particions trapezis: %.16G\n", n, trapezisabs(n));
    
    printf("Exponencial %d particions trapezis: %.16G\n", n, trapezisexp(n));

    return 0;
}

double polleg(int n, double x)
{
    double quo1=1, quo2=x,quo;
    if (n==0) return quo1;
    if(n==1) return quo2;
      
    for(int i=2; i<n+1; i++)
    {
        quo=(((2*(i-1))+1)*x*quo2)-((i-1)*quo1);
        quo=quo/i;
        quo1=quo2;
        quo2=quo;
    }
        
    return quo;
}

double polcheb(int n, double x)
{
    double quo1=1, quo2=x,quo;
    if (n==0) return quo1;
    if(n==1) return quo2;
    
    for(int i=2; i<n+1; i++)
    {
        quo=(2*x*quo2)-quo1;
        quo1=quo2;
        quo2=quo;
    }
    return quo;
}

void intervalscheb(int n, double inter[][2])
{
    int sig=0;
    int part=2;
    double p;
    
    while(sig<n)
    {
        sig=0;
        double vals[part+1];
        
        for(int i=0; i<part+1;i++)
        {
            p=i;
            vals[i]=polcheb(n,-1+(2*p/part));
        }
        for(int i=0;i<part;i++)
        {
            if(vals[i]*vals[i+1]<0) 
            {
                sig+=1;
            }
        }
        
        if(n%2==0)              //Cas per n parell on no cau cap arrel al 0
        {
            if(sig==n)          //Si hi ha prous canvis de signe en els intervals entra
            {
                int k=0;
                for(int i=0;i<part+1;i++)
                {
                    if(vals[i]*vals[i+1]<=0)
                    {
                        p=i;
                        inter[k][0]=-1+(2*p/part);
                        inter[k][1]=-1+(2*(p+1)/part);
                        k++;
                    }
                }
            }
        }
        
        else                  //Cas senar on cau una arrel al 0
        {
            if(sig==(n-1))    //Un canvi menys requerit a causa de que el 0 és arrel
            {
                int k=0;
                inter[k][0]=0;
                inter[k][1]=0;
                k++;
                
                for(int i=0;i<part+1;i++)
                {
                    if(vals[i]*vals[i+1]<0)
                    {
                        p=i;
                        inter[k][0]=-1+(2*p/part);
                        inter[k][1]=-1+(2*(p+1)/part);
                        k++;
                    }
                }
                
                for(int i=1; i<=(n/2); i++)     //Ficar els intervals en ordre correcte
                {
                    inter[i-1][0]=inter[i][0];
                    inter[i-1][1]=inter[i][1];
                }
                
                inter[n/2][0]=0;
                inter[n/2][1]=0;
                
                break;
            }
                
        }
        
        part*=2;        //Anem augmentant nombre de particions
    }
}

void intervalsleg(int n, double inter[][2])
{
    int sig=0;
    int part=2;
    double p;
    
    while(sig<n)
    {
        sig=0;
        double vals[part+1];
        
        for(int i=0; i<part+1;i++)
        {
            p=i;
            vals[i]=polleg(n,-1+(2*p/part));
        }
        for(int i=0;i<part;i++)
        {
            if(vals[i]*vals[i+1]<0) 
            {
                sig+=1;
            }
        }
        
        if(n%2==0)
        {
            if(sig==n)
            {
                int k=0;
                for(int i=0;i<part+1;i++)
                {
                    if(vals[i]*vals[i+1]<=0)
                    {
                        p=i;
                        inter[k][0]=-1+(2*p/part);
                        inter[k][1]=-1+(2*(p+1)/part);
                        k++;
                    }
                }
            }
        }
        
        else
        {
            if(sig==(n-1))
            {
                int k=0;
                inter[k][0]=0;
                inter[k][1]=0;
                k++;
                for(int i=0;i<part+1;i++)
                {
                    if(vals[i]*vals[i+1]<0)
                    {
                        p=i;
                        inter[k][0]=-1+(2*p/part);
                        inter[k][1]=-1+(2*(p+1)/part);
                        k++;
                    }
                }
                break;
            }
                
        }
        
        part*=2;
    }
}

void mig(int n, double interval[][2], double pmig[])
{
    for(int i=0; i<n; i++)
    {
        pmig[i]=(interval[i][0]+interval[i][1])/2;
    }
}

double newtonleg(double x, int n)
{
    double ant=0;
    double der;
    while(fabs(ant-x)>er)
    {
        ant=x;
        der=derivada(x,n);
        
        x=x-(polleg(n,x)/der);
    }
    return x;
}

double newtonche(double x, int n)
{
    double ant=0;
    double der;
    while(fabs(ant-x)>er)
    {
        ant=x;
        der=(-n*x*polcheb(n,x))+(n*polcheb(n-1,x));
        der=der/(1-(x*x));
        x=x-(polcheb(n,x)/der);
    }
    return x;
}

double derivada(double x,int n)
{
        double der;
        der=(-n*x*polleg(n,x))+(n*polleg(n-1,x));
        der=der/(1-(x*x));
        return der;
}

double aileg(int n, double arrel)
{    
    double ai;
    ai= 2/((1-(arrel*arrel))*derivada(arrel,n)*derivada(arrel,n));
    return ai;
}

double abs1(double x)
{
    return fabs(x);
}

double intabs1(int n, double arrels[],double ai[])
{
    double suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=ai[i]*abs1(arrels[i]);
    }
    return suma;
}

double abs2(double x)
{
    return fabs(x)*sqrt(1-(x*x));
}

double intabs2(int n, double arrels[],double ai[])
{
    double suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=ai[i]*abs2(arrels[i]);
    }
    return suma;
}

double exp1(double x)
{
    return exp(-x*x)/sqrt(1-(x*x));
}

double intexp1(int n, double arrels[],double ai[])
{
    double suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=ai[i]*exp1(arrels[i]);
    }
    return suma;
}

double exp2(double x)
{
    return exp(-x*x);
}

double intexp2(int n, double arrels[],double ai[])
{
    double suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=ai[i]*exp2(arrels[i]);
    }
    return suma;
}

double trapezisabs(int particions)
{
    double suma=0, aux=0;
    double nodes[particions+1];
    double fnodes[particions+1];
    double h=2./particions;
    
    for(int i=0; i<particions+1; i++)
    {
        nodes[i]=-1+aux*h;
        aux++;
    }
    
    for(int i=0; i<particions+1;i++)
    {
        fnodes[i]=abs1(nodes[i]);
    }
    for(int i=1; i<particions;i++)
    {
        suma+=fnodes[i]*2;
    }
    
    suma= (suma+fnodes[0]+fnodes[particions])*h/2;
    
    return suma;
}

double trapezisexp(int particions)
{
    double suma=0, aux=1;
    double nodes[particions+1];
    double fnodes[particions+1];
    nodes[0]=-0.9999;
    nodes[particions]=0.9999;
    double h=nodes[particions]-nodes[0]/particions;
    

    
    for(int i=1; i<particions; i++)
    {
        nodes[i]=-1+aux*h;
        aux++;
    }
    
    for(int i=0; i<particions+1;i++)
    {
        fnodes[i]=exp1(nodes[i]);
    }
    for(int i=1; i<particions;i++)
    {
        suma+=fnodes[i]*2;
    }
    
    suma= (suma+fnodes[0]+fnodes[particions])*h/2;
    
    return suma;
}