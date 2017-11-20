class M3_2 {
  public static void main(String args[]) {
    int year = 0;

    switch(args[0]){
      case "s":
      case "S":
        year = 1925 + Integer.parseInt(args[1]);
      break;
      case "h":
      case "H":
        year = 1988 + Integer.parseInt(args[1]);
      break;
      default: System.exit(1);
    }

    System.out.println("YEAR:" + year);
  }
}
