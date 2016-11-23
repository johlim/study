import random
global lives_remaining
global display_word
global display_word

words=["chicken", "dog", "cat"," mouse","frog"]

lives_remaining=14
guessed_letters=""

def say_hello(sentence):
    print(sentence+"^^")
    return

def pick_a_word():
    return random.choice(words)

def print_word_with_blanks(word):
    display_word=""
    for letter in word:
        if guessed_letters.find(letter) > -1:
            display_word = display_word + letter
        else:
            display_word = display_world + '-'
    print(display_word)

def get_guess(word):
    print_word_with_blanks(word)
    print('Live Remaining:'+str(lives_remaining))
    guess  = input('Guess a letter or whole word?')
    return guess

def single_letter_guess(guess,  word):    
    if word.find(guess) == -1:
        lives_remaining = lives_remaining -1
    guessed_letters = guessed_letters + guess
    if all_letters_guessed(word):
        return True
    return False

def all_letters_guess(guess,  word):    
    global guessed_letters
    for letter in word:
        if guessed_letters.find(letter) == -1:
            return False
        return True

def whole_word_guess(guess,  word):
    global lives_remaining   
    if guess == word:
        return True
    else:
          lives_remaining = lives_remaining -1
          return False
    
    guessed_letters = guessed_letters + guess
    return False


def process_guess(guess,  word):
    global lives_remaining
    global guessed_letters
    lives_remaining = lives_remaining - 1
    guessed_letters = guessed_letters + guess
    return False
    

def play():
    word = pick_a_word()
    while True:
        guess = get_guess(word)
        if process_guess(guess,  word):
            print('You win')
            break
        if live_remaing==0:
            print('you are end')
            print('The word was :'+word)
            break
            
play()
