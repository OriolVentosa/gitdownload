int mortalitat;
int anybenef;
int pr;

int despesesarbre(int,int, int, int);
int anycomp(int, int, int);
int consumanual(int [mortalitat],int, int);
int consumanualsegur(int [mortalitat],int,int);

int despesesarbre(int k,int dmaxima, int preukg, int plant) //negatiu
{
    float any;
    int anyint;
    for(int i=k;i<31;i++)
    {
            any = (i*i)/6;
            anyint=any*preukg;
            if(anyint>dmaxima) 
            {
                if(pr!=1)
                {
                    anybenef=i;
                    pr=1;
                }
                break;
            }
    }
    
    for(int i=k;i<anybenef;i++)
    {
            any = (i*i)/6;
            anyint=any*preukg;
            plant= plant+anyint-dmaxima;
    }
    
    return plant;
}

int anycomp(int dmaxima, int preukg, int plant)
{

    float any;
    int anyint;
    for(int i=0;i<31;i++)
    {
        if(i<31)
        {
            any = (i*i)/6;
            anyint=any;
        }

        else
        {
            any=-((i*i)/10)+250;
            anyint=any;
            if(anyint<0) anyint=0;
        }

        plant=plant+anyint-dmaxima;
        if(plant>0) return i;
    }
    
    return 0;
    
}


int consumanual(int arbres[mortalitat],int dminima, int dmaxima)
{
    int total=0;

    for(int i=0; i<mortalitat;i++)
    {
        total=total+arbres[i];
    }

    int aleatori = dmaxima-dminima;

    int danuals;

    danuals = rand() % aleatori;

    danuals=danuals+dminima;

    danuals = danuals*total;

    return danuals;
}

int consumanualsegur(int arbres[mortalitat],int dminima, int dmaxima)
{

    int total=0;

    int aleatori = dmaxima-dminima;

    int danuals;

    for(int i=0; i<mortalitat;i++)
    {
        total=total+arbres[i];
    }

    for(int i=0; i<anybenef;i++)
    {
        total=total-arbres[i];
    }

    danuals = rand() % aleatori;

    danuals=danuals+dminima;

    danuals = danuals*total;

    return danuals;
}