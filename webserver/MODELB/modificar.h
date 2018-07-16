int mortalitat, anybenef, despeseslimit, plant, pr=0;

void modificarllista(int [mortalitat], double);

int plantar(int*, long long int*,int[anybenef], int [mortalitat],int*, int, int, int);

int armor(int[mortalitat], int[anybenef], int, int, int, int);  //treu les despeses dels arbres que moren

void modificarllista(int edats[mortalitat], double permortalitat)
{
//     srand(time(NULL));
    
    int probabilitat[mortalitat];
    int posicio=0;
    
    for(int i=0; i<mortalitat;i++) //mortalitat
    {
        probabilitat[i]=0;
    }
    for(int i=0; i<mortalitat;i++) //mortalitat
    {
        probabilitat[i]=posicio+edats[i];
        posicio=posicio+edats[i];
    }
    
    permortalitat=permortalitat*posicio;
    
    int random;
    for(int i=0;i<permortalitat;i++) //percentatge de mort
    {
        if(posicio!=0)
        {
            random=rand()%posicio;  //arreglar random
            if(random==0) random+=1;

            for(int j=0;j<mortalitat;j++)
            {
                if(random<=probabilitat[j])
                {
                    edats[j]=edats[j]-1;
                    for(int k=j; k<mortalitat;k++)
                    {
                        probabilitat[k]=probabilitat[k]-1;
                    }
                    posicio=posicio-1;
                    break;
                }
            }
        }
    }
    
    int edatscanvi[mortalitat];
    
    for(int i=0; i<mortalitat; i++)
    {
        edatscanvi[i]=0;
    }

    int a;
    
    for(int i=0; i<mortalitat-1; i++)
    {
        a= (i-1+mortalitat)%mortalitat;
        edatscanvi[i]=edats[a];
    }

    edatscanvi[0]=0;

    for(int i=0; i<mortalitat; i++)
    {
        edats[i]=edatscanvi[i];
    }
}

int plantar(int *despeses, long long int *despesesb, int arbres[anybenef], int arbrestotals[mortalitat],int *contador, int desxar, int anyactual, int arbresmax) //despeses segure/llista arbres plantats/llista anys quan s'ha plantats/longitud llista
{
    int arbrespl=0;
    int total=0;

    for(int i=0;i<mortalitat;i++)
    {
        total=total+arbrestotals[i];
    }

    
    if(total<arbresmax)
    {
        while(1<2)
        {
            *despeses=*despeses+desxar;
            *despesesb=*despesesb+plant;
            arbrespl+=1;
            total+=1;
            if(*despeses<despeseslimit || total>arbresmax)
            {
                *despeses=*despeses-desxar;
                *despesesb=*despesesb-plant;
                arbrespl-=1;
                total-=1;
                break;
            }
        }
    }

    
    if(*contador == anybenef)
    {
        for(int i=0; i<anybenef-1; i++)
        {
            arbres[i]=arbres[i+1];
        }
        *contador-=1;
    }
    
    
    arbres[*contador]=arbrespl;
    *contador+=1;

    return arbrespl;
}

int armor(int edats[mortalitat], int arbres[anybenef], int despesessegures, int contador,int despesesmax, int pkg)
{
    int a,b,c;
    for(int i=0; i<contador; i++)
    {
        a=edats[i]-arbres[contador-1-i];
        b=despesesarbre(i, despesesmax, pkg, plant);
        c+=a*b;
        arbres[contador-1-i]=edats[i];
    }
    return despesessegures+c;
}