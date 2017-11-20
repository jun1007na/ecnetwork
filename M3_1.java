class M3_1 {
  public static void main(String args[]) {
    int max=0;
    int array;

    for(int i=0; i<args.length; i++){
      array = Integer.parseInt(args[i]);
      if(array > max) max = array;
    }
    System.out.println("Max:" + max);
  }
}
