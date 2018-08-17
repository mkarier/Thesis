import java.util.*;
import java.io.*;

public class ProcessAlphabet
{
	public static int numFiles = 52;
	public static int numDatabase = 52;
	public static double secondSmallest = Double.MAX_VALUE;
	public static double thirdSmallest = Double.MAX_VALUE;
	public static double fourthSmallest = Double.MAX_VALUE;
	public static double fifthSmallest = Double.MAX_VALUE;
	
	public static double largest = Double.MIN_VALUE;
	public static double secondLargest = Double.MIN_VALUE;
	public static double thirdLargest = Double.MIN_VALUE;
	public static double fourthLargest = Double.MIN_VALUE;
	

	public static void main(String... args)
	{
		printHeaders();
		for(int i = 1; i <= numFiles; i++)
		{
			printFiles(i);
		}//end of for loop to look to parse data
		try
		{
			BufferedWriter out = new BufferedWriter(new FileWriter("ranges.txt"));
			out.write("Second Smallest: "+ secondSmallest + "\n");
			out.write("Third Smallest: " + thirdSmallest + "\n");
			out.write("Fourth Smallest: " + fourthSmallest + "\n");
			out.write("Fifth Smallest: " + fifthSmallest + "\n");
			out.write("Largest: " + largest + "\n");
			out.write("secondLargest: " + secondLargest + "\n");
			out.write("thirdLargest: " + thirdLargest + "\n");
			out.write("fourthLargest: " + fourthLargest + "\n");
			out.close();
		}
		catch(IOException e)
		{
			System.out.println(e);
		}
	}//end of main

	public static void printHeaders()
	{
		//System.out.print(0 + ",foundSelf");
		System.out.print("Names");
		for(char index = 'A'; index <= 'Z'; index++)
		{
			System.out.print(","+index);
		}//end of for loop to output headers
		for(char index = 'a'; index <= 'z'; index++)
		{
			System.out.print(","+index);
		}//end of for loop to output headers
		System.out.println();
	}//end of printHeaders
	
	public static void printFiles(int o_num)
	{
		String originalFile = "scan1-"+o_num+".png";
		try
		{		
			BufferedReader in = new BufferedReader(new FileReader("test"+o_num+".txt"));
			String buffer = in.readLine();
			int foundSelf = 0;
			double fileCount[]= new double[numDatabase+1];
			while(buffer!= null)
			{
				/*if(originalFile.compareTo(buffer) == 0)
					foundSelf=1;//*/
				String firstSplit[] = buffer.split("scan1-");
				String secondSplit[] = firstSplit[1].split(".png");
				//System.out.println(secondSplit[0]);
				int similarContours = Integer.parseInt(secondSplit[0]);
				double totalContours = 0;
				if(secondSplit[1].contains("inf"))
					totalContours = Double.MAX_VALUE;
				else
					totalContours = Double.parseDouble(secondSplit[1]);
				fileCount[similarContours] = totalContours;
				findRanges(totalContours);
				buffer = in.readLine();
			}
			in.close();
			//System.out.print(originalFile+","+foundSelf);
			System.out.print(originalFile);
			for(int i = 1; i <= numDatabase; i++)
			{
				System.out.print(","+fileCount[i]);
			}
			System.out.println();					
		}
		catch(IOException e)
		{
			System.out.println(e);
		}
	}//end of printFiles
	
	public static void findRanges(double input)
	{
		findSmallest(input);
		findLargest(input);
	}
	public static void findSmallest(double input)
	{
		boolean changeSecond = false;
		boolean changeThird = false;
		boolean changeFourth = false;
		boolean changeFifth = false;
		if(input != 0)
		{
			if(input < secondSmallest)
				changeSecond = true;
			if(input < thirdSmallest && thirdSmallest > secondSmallest)
				changeThird = true;
			if(input < fourthSmallest && fourthSmallest > thirdSmallest)
				changeFourth = true;
			if(input < fifthSmallest && fifthSmallest > fourthSmallest)
				changeFifth = true;
		}
		if(changeSecond)
			secondSmallest = input;
		else if(changeThird)
			thirdSmallest = input;
		else if(changeFourth)
			fourthSmallest = input;
		else if(changeFifth)
			fifthSmallest = input;
		
	}
	
	public static void findLargest(double input)
	{
		boolean changeSecond = false;
		boolean changeThird = false;
		boolean changeFourth = false;
		boolean changeFifth = false;
		if(input !=  Double.MAX_VALUE)
		{
			if(input > largest)
				changeSecond = true;
			if(input > secondLargest && secondLargest < largest)
				changeThird = true;
			if(input > thirdLargest && thirdLargest < secondLargest)
				changeFourth = true;
			if(input > fourthLargest && fourthLargest < thirdLargest)
				changeFifth = true;
		}
		if(changeSecond)
			largest = input;
		else if(changeThird)
			secondLargest = input;
		else if(changeFourth)
			thirdLargest = input;
		else if(changeFifth)
			fourthLargest = input;
	}
}//end of class ProcessResults
