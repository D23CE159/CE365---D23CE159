class RDP:
    def __init__(self, string):
        self.string = string
        self.index = 0

    def match(self, char):
        if self.index < len(self.string) and self.string[self.index] == char:
            self.index += 1
            return True
        return False
    
    def Z(self):
        start = self.index
        if self.B():
            return self.Z_dash()
        self.index = start
        return False
    
    def Z_dash(self):
        start = self.index
        if self.match('a') and self.match('b'):
            return True
        self.index = start
        if self.match('x') and self.match('y'):
            return True
        self.index = start
        return True

    def Z(self):
        start = self.index
        if self.B():
            return True
        self.index = start
        if self.Z():
            if self.match('a') and self.match('b'):
                return True
            elif self.match('x') and self.match('y'):
                return True
        self.index = start
        return False
    
    def B(self):
        start = self.index
        if self.match('a') and self.match('b'):
            if self.D() and self.match('g'):
                return True
            return True
        self.index = start

        if self.match('c') and self.match('d'):
            if self.D() and self.match('h'):
                return True
            return True
        self.index = start
        return False
    
    def D(self):
        start = self.index
        if self.match('p') and self.match('q'):
            return True
        self.index = start

        if self.match('r') and self.match('s'):
            return True
        self.index = start
        return False
    
    def valid(self):
        if self.Z() and self.index == len(self.string):
            print("String is VAlid!")
        else:
            print("String is Invalid!")

condition = True
while (condition):
    string = input("Enter the string: ")
    if (string == "exit"):
        condition = False
    else:
        parsing = RDP(string)
        parsing.valid()

