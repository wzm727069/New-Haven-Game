# COMP 345 Project - Advanced C++ Programming

# Project Description

A playable version of New Haven game written in C++. The New Haven is a “tactical” game, the gaming rules are given in [1]. The three assignments will be about the development of different parts of a project. Thus, every assignment will build upon code developed in the previous assignments. You are expected to work in teams of 4 for every assignment. Individual work will be accepted, but will be graded in the same terms as team work.

New Havengame is a multiplayer board game (2 to 4players). The developed program will have to be compatible with the rules, componentsand the play of the game. The New Havengame consists of 
* a Game Board (side Aand B),and 
* the players’ Village Game Boards (max 4).
  * The Game Board consists of:
    * playing area, which is a connected graph mapwhere nodes are squares where each player puts the Harvest       
    Tilesandedgesrepresent adjacency between the harvest tiles.
    * an area for theavailable Buildingstokens.
    * a numbered area for Resource Track.
  * 4 Player Village Game Boards: each Village Game Boardis a map used to build the village. 
  
Each player attempts to build a village in New England that will attract the most colonists by the end of the game.Resources will be gathered and used to attract tradesman and craftsman and better amenities for each village. The village that attracts the largest number of colonists will win.


<h2 id="GC">Game Components</h2>

 * Game Board two sides (A and B)
 * 4 Village Game Boards
 * 4 Pond Tiles (use only with side B game board)
 * 60 <em>Harvest Tildes</em>, each tile is divided into 4 squares showing 2 or 3 different resources
 * 144 Buildings, 6 Buildings in each of the four colors numbered from 1 to 6. (The opposide side of each building has either a meadow, quarry, forest or wheatfield)
 * 4 Player Screens
 * 4 Resource Markers

<h2 id="FP">Features and Parts of the game</h2>
Map: The game consistsof 
* one Game Board and 
* 4 player Village Boardsgame. 

The Game Board is considered as a map, that is a <em> connected graph</em> where each node represents a square for a Harvest Tile and edges between the nodes represent adjacency between Harvest tiles. During gameplay, players put their Harvest tiles on the playing area of the Game Board, and the Buildings available as well as Resource Track.

The Village Game board is a 5 by 6 map of circular spaces. The spaces on the Village Game board are marked with numbers to show the cost to play on that space. The figures at the side and bottom show colonists (and therefore score) that will be gained by completing a row or column. Each player owns one Village Game.

<h2 id="GP"> Game Phases </h2>
    <h3>Setup phase</h3>
    <ol>
    <li> The board map (A or B)</li>
      <li> Game of: 
        <ol>
          <li> four players, the entire playing area will be used.</li>
          <li> three players, the light center 5x5 area and the top bottom green squares will be used </li>
          <li> two players, only the center 5x5 area is used. </li>
        </ol>
        <li> The four resource markers are placed on the zero space of the Resource Track on the Game Board. </li>
        <li>Each player takes a Village Board. This board represents the local Village that each player is developing.
        The space are marked with numbers to show the cost to play on that space. The figures at the side and bottom    
        show colonists (and therefore score) that will be gained by completing a row or column.</li>
      <li>The 60 Harvest Tiles(face hidden to players) are loaded and shuffled thoroughly to form a pool from which to   
        draw.</li>
      <li>All 144 Buildings are loaded to be drawn randomly. </li>
      <li>Five Buildings are drawn out and place in the circles at the edge of the board to form the initial face up 
        pool. Each Building is marked with its’ coston  the  left  side  and  resource needed on the right.</li>
      <li>Each player takes a Player Screen and draws six Buildings in secret from the pool and two Harvest Tiles from  
        the  pool  and  places  all  of  them  behind  the  screen. Player’s Harvest Tiles and Buildings are private 
        and need not be disclosed.</li>
      <li>Each playeris given one Harvest Tile placed face down beside their Village Board as their ‘shipment’ 
        tile.This tile is not known until after it has been played. This tile represents the opportunity that once  
        per game a playermay receive  4 of the same resources and temporarily ignore what is actually on the 
        tile.</li>
      </ol></li>
      <h3>Game Playing Overview</h3>
      <ul>
        <li><em>The player with the smallest student ID number will begin.</em> Play continues with each player taking 
          a turn clockwise until one space is left unfilled on the board. The game ends when there is only one space 
          left on the board. Each player will take an equal number of turns</li>
        <li>On each turn the active player begins by selection one of their Harvest Tiles and placing it onto the Game 
          Board. This play will generate a supply of Resources. The amount of Resources collected is indicated by 
          increasing the Resource Markers on the track beside the Game Board. The active player will then construct 
          Buildings in their Village by using the corresponding Resources. When the active player is finished , each 
          of other player in clockwise order will have the option of also using any remaning Resources to construct 
          Buildings in their own Village</li>
        <li>After everyone has had one chance to build or passes, the active player draws a new Buildings based on the 
          final position of the Resource Markers. The Resource Markers are then returned to a zero value and the 
          player draws a new Harvest Tile to replace the one just played. The selection of face up BUildings is 
          replenished and the play proceeeds with the next player clockwise turn</li>
      </ul>
    
  <h3>Game End Sequence</h3>
    <ul>
      <li>The game ends <em>when there is exactly one open space left</em> on the Game Board.</li>
      <li>The Scoring  is  based  on  how  many  Colonists  each  player  has  attracted  to  his/her  Village. Score  
        points for  every  row  and column  that  is  completely filled  with  Buildings.  The  value  of each row and 
        column is the number of Colonists shown at the right or bottom. Note: the value of  a  row  or  column  is 
        doubled  if  every Building  played  on  that  row  or  column  is  face  up. Buildings leftover behind Player 
        Screens at the end of the game do not score but may be a tie-breaker</li>
      <li>The player with the highest score is the winner. In the event of a tie, the player with the fewest empty 
        spaces on their board wins. If still tied, then the player with the least buildings leftover wins. If this 
        result is still a tie then it is a shared win between those players.
      </li>
    </ul>

<p id="CS"></p>
