# Chunkstruction
Dead project on UE4.13 (making construction with blocks by using chunks) reason of fail: adding physics

Frame : Actor which contains all chunks of the same construction
BlockTypes : a class wich contains each different BlockType
BlockType : Parent class of each Block wish contains all of there logic to render them
Block : a struct wich is used as a memory for Block
MyCharacter : the Charcter class
MeshData : struct wich is used to store geometric data
Direction : enum of each direction
ChunkstructionGameMode : the Game Mode
ChunkComponent : component wich store Block and can be rendered
