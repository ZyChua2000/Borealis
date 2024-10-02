Scene: SceneName
Entities:
  - EntityID: 8047060871641484140
    TagComponent:
      Tag: testBehaviourTree
    TransformComponent:
      Translate: [0, 0, 0]
      Rotation: [0, 0, 0]
      Scale: [1, 1, 1]
    BehaviourTreeComponent:
      BehaviourTree:
        Tree Name: Test-Tree
        name: C_Sequencer
        depth: -842150451
        children:
          - name: L_Idle
            depth: 1
          - name: L_CheckMouseClick
            depth: 1