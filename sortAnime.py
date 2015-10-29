def sortAndUpdate():
	with open('animeList.txt', 'r') as f:
		words = f.readlines()
		#Strip the words of the newline characters (you may or may not want to do this):
		words.sort()

	fileOpen = open('animeList.txt', 'w')
	fileOpen.writelines(words)
	fileOpen.close()

#this should work now
sortAndUpdate()


exit(0)
