# TODO
from cs50 import get_float
def main():
   count =0
   answer = 0
   cents = 0
   while answer <= 0:
       answer = get_float("Change owed: ")
       cents = round(answer * 100)
   while cents > 0:
       if cents >=25:
           cents = cents -25
           count = count +1
       elif cents >= 10:
           cents = cents - 10
           count = count + 1
       elif cents >= 5:
           cents = cents -5
           count = count +1
       elif cents >= 1:
           cents = cents -1
           count = count + 1
   print(count)


if __name__ == "__main__":
    main()
