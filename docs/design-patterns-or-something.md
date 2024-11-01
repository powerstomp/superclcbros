## Game loop

Update entities (velocity, animation, ...) -> Physics engine -> Render

Physics engine: Move entities -> Check collision -> Resolve (push colliders away and signal to observer)

# Design patterns

## Service Locator & Flyweight pattern

```mermaid
sequenceDiagram
    participant Entity
    participant StateMenu
    participant ServiceLocator
    participant TextureManager

    Entity->>ServiceLocator: Get<TextureManager>()
    ServiceLocator-->>Entity: TextureManager
    Entity->>TextureManager: Get(texturePath)
```

Since the texture manager "shares" texture data between different instances of Goomba, etc... this is also an instance of the Flyweight pattern.

## Factory pattern

```mermaid
sequenceDiagram
    participant LevelFile
    participant MakeEntity
    participant MakeTile
    participant Level

    LevelFile->>MakeEntity: calls MakeEntity(id)
    MakeEntity-->>Level: produces Entity
    LevelFile->>MakeTile: calls MakeTile(id)
    MakeTile-->>Level: produces Tile
```

## Observer pattern

```mermaid
sequenceDiagram
    participant PhysicsEngine
    participant Observer
    participant Entity
    participant GameData

    PhysicsEngine->>Observer: detects collision and sends signal
    Observer->>Entity: notify listeners about collision
    alt Player entity
        Entity-->>Entity: death animation
        Entity->>GameData: player died
        GameData->>GameData: remove lives
        GameData->>GameData: restart level
    else Goomba entity
        Entity-->>GameData: stomped
        GameData->>GameData: add coins
        GameData->>GameData: add combo
    end
```

## State pattern

```mermaid
sequenceDiagram
    participant Game
    participant State (Current)
    participant Window (SFML)

    loop Game Loop
        Game->>State (Current): GetState().Update()
        State (Current)-->>Game: Update logic

        Game->>State (Current): GetState().Render(deltaTime)
        State (Current)-->>Window (SFML): Render graphics

        loop Handle events
                Window (SFML)-->>Game: Event data
                Game->>State (Current): GetState().OnSFMLEvent(event)
                State (Current)-->>Game: Handle event

        end
    end

```
