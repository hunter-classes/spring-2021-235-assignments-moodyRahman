
int david(int n)
{
    if (n == 1)
    {
       return 1;
    }
    
    if (n == 2)
    {
        return 2;
    }
    
    if (n == 3)
    {
        return 4;
    }
    
    if (n <= 0)
    {
        return 0;
    }
    
    return david(n - 1) + david(n - 2) + david(n-3);
}