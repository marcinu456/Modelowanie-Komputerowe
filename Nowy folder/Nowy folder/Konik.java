/*
Problem konika (skoczka) szachowego
www.algorytm.org
Adam Mika, Tomasz Lubinski (c) 2008

Algorytm podaje pierwsze dopuszczalne rozwi�zanie problemu dla podanego punktu startowego
pod warunkiem, �e takie rozwi�zanie istnieje.
*/


public class Konik {

	/**
	 Problem konika (skoczka) szachowego
	 www.algorytm.org
	 Adam Mika, Tomasz Lubinski (c) 2008

	Algorytm podaje pierwsze dopuszczalne rozwi�zanie problemu dla podanego punktu startowego
	pod warunkiem, �e takie rozwi�zanie istnieje.
	*/
	public static void main(String[] args) {
		   int max = 8;	//rozmiar problemu - wymiar szachownicy
		   int tab[][] = new int[max][max];
		      
		   for(int i=0 ; i<max ; i++)
		      for(int j=0 ; j<max ; j++)
		         tab[i][j] = 0;
		   
		   if (skoczek(tab, max, 0, 1, 1) == true)
		   {
			   	for(int i=0 ; i<max ; i++)
			   	{
			   		for(int j=0 ; j<max ; j++)
			   			System.out.print(tab[j][i] + " ");
			   		System.out.println();
			   	}
		   }
	}
	
	private static boolean ruch(int tab[][], int N, int wariant, int x, int y, int nx[], int ny[])
	{
	    switch (wariant) {
	    case 1: 
	           nx[0] = x+1; 
	           ny[0] = y-2;
	           break;
	    case 2:
	           nx[0] = x+2;
	           ny[0] = y-1;
	           break;
	    case 3:
	           nx[0] = x+2;
	           ny[0] = y+1;
	           break;
	    case 4: 
	           nx[0] = x+1;
	           ny[0] = y+2;
	           break;
	    case 5:
	           nx[0] = x-1;
	           ny[0] = y+2;
	           break;
	    case 6:
	           nx[0] = x-2;
	           ny[0] = y+1;
	           break;
	    case 7:
	           nx[0] = x-2;
	           ny[0] = y-1;
	           break;
	    case 8:
	           nx[0] = x-1;
	           ny[0] = y-2;
	           break;
	    }   
	    if (0<=nx[0] && nx[0]<N && 0<=ny[0] && ny[0]<N && tab[nx[0]][ny[0]]==0)
	       return true;
	    return false;                            
	}   

	public static boolean skoczek(int tab[][], int n, int x, int y, int ktory)
	{
	   int nx[] = new int[1];
	   int ny[] = new int[1];
	   
	   nx[0] = 0;
	   ny[0] = 0;
	   tab[x][y] = ktory;
	   
	   if(ktory == n*n)
	   { 
	      return true;
	   }   
	   else
	   {
	      for(int w=1 ; w<9 ; w++)
	        if(ruch(tab, n, w, x, y, nx, ny) == true)
	          if (skoczek(tab, n, nx[0], ny[0], ktory+1) == true)
	        	  return true;
	      tab[x][y] = 0;
	   }
	   return false;
	} 

}
