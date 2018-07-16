int mortalitat, anybenef;

int kgrecolectats(int [mortalitat]);
int kgrecolectatsegurs(int [mortalitat], int [anybenef], int);

int kgrecolectats(int edats[mortalitat])
{
    int kg=0;
    float any;
    int anyint;

    for(int i=0;i<mortalitat;i++)
    {
        if(i<31)
        {
            any = (i*i)/6;
            any = any*edats[i];
            anyint=any;
        }

        else
        {
            any=-((i*i)/10)+250;
            any = any*edats[i];
            anyint=any;
            if(anyint<0) anyint=0;
        }

        kg=kg+anyint;
    }

    return kg;
}

int kgrecolectatsegurs(int arbres[mortalitat], int arbresplantats[anybenef], int anyactual)
{
    
    int kg=0;
    float any;
    int anyint;

    for(int i=0;i<mortalitat;i++)
    {
        if(i<31)
        {
            any = (i*i)/6;
            any = any*arbres[i];
            anyint=any;
        }

        else
        {
            any=-((i*i)/10)+250;
            any = any*arbres[i];
            anyint=any;
            if(anyint<0) anyint=0;
        }
        kg=kg+anyint;
    }
    if(anyactual<=anybenef)
    {
        for(int i=0;i<=anyactual;i++)
        {
            any = (i*i)/6;
            any = any*arbres[i];
            anyint=any;
            kg=kg-anyint;
        }
    }
    else
    {
        for(int i=0;i<anybenef;i++)
        {
            any = (i*i)/6;
            any = any*arbres[i];
            anyint=any;
            kg=kg-anyint;
        }
    }

    return kg;
}