How to change/add textures:

For crashes on leaks meme textures:
multiple texture can be saved in the repositories assiciated to CRASHES or LEAKS in the map (in the maps given in the project they are crashes/ or leaks/)
	-- animated textures are in subdirectories(containing frames as .xpm ordered by ascii value(*1), a frame_data.txt files must be in it and contain two lines: the first one is the delay in ms between two frames, the second one is the pause delay between the last frame and the cycling first one)
	-- single textures not animated are directly present as a .xpm file

For any other texture:
in a repository named as described in the map:
	just drop all the .xpm files, if they are multiple ones the texture will be animated (*1)

(*1) multiple .xpm files that are parts of a same animated texture: their ascci order must correspond to the chronological order of the frames