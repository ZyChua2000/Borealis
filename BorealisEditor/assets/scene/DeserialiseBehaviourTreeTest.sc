Scene: SceneName
Entities:
  - EntityID: 10861269917063479940
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
        depth: 0
        children:
          - name: L_Idle
            depth: 1
          - name: L_CheckMouseClick
            depth: 1