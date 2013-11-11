import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.io.*;

/**
 * Find a pair of numbers in an array given a target sum
 * 
 *
 */

public class FindNums {

    public static int findSumsForTarget(int[] input)
    {
        // just print it instead of returning
		int sum = 0;
		boolean exit;
        Map<Integer, String> myMap = populateMap(input);
        
		for (int j = 2500; j <= 4000; j++){
	         exit = false;
			// iterate over key set
			for (Integer currKey : myMap.keySet()) {
				// find the diff
			    Integer diff = j - currKey;
					// check if diff exists in the map
			    	String diffMapValue = myMap.get(diff);
			    	if(diffMapValue!=null){
			       		// sum exists
						if (diff != currKey && currKey != 0 && diff != 0){
			       			sum++;
				   			exit = true;
					        String output = "target " + j + " x " + currKey + " y " + diff;   
					        System.out.println(output);
			    		}
					}
			    if (exit)
			       break;
			}
		}

		return sum;
    }

    private static Map<Integer, String> populateMap(int[] input) 
    {
        Map<Integer,String> myMap = new HashMap<Integer,String>();
        for (int i = 0; i < input.length; i++) {
             String currInputVal = myMap.get(input[i]);
             if(currInputVal==null) // value not exists
                 myMap.put(input[i], Integer.toString(i)); // first argument is autoboxed to Integer class                               
        }               

        return myMap;
    }


    // test it out!
    public static void main(String[] args)
    {
		int [] input = new int [500000];
		Scanner scanner;
		int i = 0;
		int sum = 0;
		try {
			 scanner = new Scanner(new File("HashInt.txt"));
			while(scanner.hasNextInt()){
			   input[i++] = scanner.nextInt();
			}
			String output1 = "ok ";   
	        System.out.println(output1);
	        // test
	        	sum = FindNums.findSumsForTarget(input);

	        String output = "Sum " + sum;   
	        System.out.println(output);
		        } catch (FileNotFoundException e) {
		            // TODO Auto-generated catch block
		            e.printStackTrace();
		        }
		

    }


}