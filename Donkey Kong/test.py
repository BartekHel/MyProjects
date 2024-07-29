import gymnasium as gym
from random import seed
from random import randint
import random

#Mario red color = (200, 72, 72)
#barrel color = (236, 200, 96)
#violet color = (181, 108, 224)

#tablen = 1600

#height lvl 1 = 176
#height lvl 2 = 155
#height lvl 3 = 127

class Mario:
   def __init__(self) -> None:
      self.distance = 0
      self.height = 0
      self.genes = []
      self.finalLocation = (0, 0)
      self.reward = False
      self.probability = 0
   def generateGenes(self, tabLen):
      seed()
      for i in range(tabLen):
         self.genes.append(randint(2, 4))
   def mutate(self, tabLen):
      for i in range(tabLen):
         prob = random.random()
         if prob < 0.05:
            self.genes[i] = randint(2, 4)

   def saveToFile(self, generation):
      file = open("WinnerMarioGen20.txt", "a")
      file.write(f"Mario generacja {generation}: ")
      for gene in self.genes:
         file.write(f"{gene} ")
      file.write("\n")
      file.close()
   def readFromFile(self, marioGen):
      with open("WinnerMarioGen20.txt") as file:
         for line in file:
            tab = line.split(" ")
            if(tab[0] == "Mario" and tab[2][:len(tab[2])-1] == str(marioGen)):
               self.genes = tab[3:]


def mate(marioMom, marioDad, tabLen):
   marioChild = Mario()
   for i in range(tabLen):
      prob = random.random()

      if prob < 0.5: #geny od matki
         marioChild.genes.append(marioMom.genes[i])
      else: #geny od ojca
         marioChild.genes.append(marioDad.genes[i])
   return marioChild

def findRed(n):
   for i, row in enumerate(n):
      for j, col in enumerate(row):
         if col[0] == 200 and col[1] == 72 and col[2] == 72:
            if i != 26 and j != 66:
               return (i, j)
            
def calculateProbability(sortedMarios, sumDistance):
   #obliczamy prawdopodobienstwo z jakim dany Mario zostanie wybrany ze wzoru fitness / overall fitness
   for mario in sortedMarios:
      mario.probability = abs(mario.distance) / sumDistance
   #wybieramy prawdopodobienstwo najslabszego Mario
   weakestMarioProbability = sortedMarios[-1].probability
   index = -1
   while(weakestMarioProbability == 0):
      weakestMarioProbability = sortedMarios[index - 1].probability
      index -= 1
   rouletteSelectionList = []
   #wpisujemy do listy Mario tyle razy ile razy jego prawdopodobienstwo jest wieksze od prawdopodobienstwa najslabszego Mario 
   for mario in sortedMarios:
      numberOfRepetitions = int(mario.probability // weakestMarioProbability)
      for i in range(numberOfRepetitions):
         rouletteSelectionList.append(mario)
   return rouletteSelectionList

def testMario(env, mario):
   hatLength = 3
   #ruchy = [2,3,4,11,12]
   previousLocation = 47
   observation, reward, terminated, truncated, info = env.step(1)
   for move in range(len(mario.genes)):
      #action = env.action_space.sample()  # this is where you would insert your policy
      action = mario.genes[move]
      red_location = findRed(observation)
      if red_location is None:
         continue
      #print(red_location)
      if red_location[0] > 165 or (red_location[0] < 135 and red_location[0] > 105) or (red_location[0] < 85 and red_location[0] > 48):
         mario.distance += red_location[1] - previousLocation
      else:
         mario.distance += -red_location[1] + previousLocation
      for i in range(red_location[1] - 6, red_location[1] + hatLength + 7):
         for j in range(red_location[0], red_location[0] + 10):
            if i < 0 or j < 0:
               continue
            if(observation[j][i][0] == 236 and observation[j][i][1] == 200 and observation[j][i][2] == 96):
               if i > red_location[1]:
                  #print("Prawa")
                  action = 11
                  break
               else:
                  #print("Lewa")
                  action = 12
                  break
            """
            elif(observation[j][i][0] == 181 and observation[j][i][1] == 108 and observation[j][i][2] == 224):
               if j < red_location[0] + 1 and ( i > red_location[1] - 2 and i < red_location[1] + hatLength + 2):
                  #print("drabinka")
                  chance = randint(0, 9)
                  if chance == 1:
                     #action = 2
                     action = 0
                  break
            """
      #print(red_location)
      observation, reward, terminated, truncated, info = env.step(action)
      previousLocation = red_location[1]
      if terminated or truncated or info["lives"] < 2:
         break
   if reward > 0:
      mario.reward = True
   mario.finalLocation = red_location
   observation, info = env.reset()

def train():
   env = gym.make("ALE/DonkeyKong-v5")
   observation, info = env.reset(seed=42)
   tabLen = 1600

   populationSize = 20
   generation = 1
   found = False
   population = []
   sumDistance = 0
   
   for _ in range(populationSize):
      mario = Mario()
      mario.generateGenes(tabLen)
      testMario(env, mario)
      sumDistance += abs(mario.distance)
      population.append(mario)

   while not found:
      population = sorted(population, key= lambda x:x.distance, reverse= True)
      population[0].saveToFile(generation)
      if population[0].reward == True:
         found = True
         print("Finished")
         break

      print(f"Generacja = {generation}, dystans Mario = {population[0].distance}")
      newGeneration = []
      """
      #10% najbardziej sprawnych z poprzedniej generacji przechodzi do nowej generacji
      s = int((10*populationSize)/100)
      newGeneration.extend(population[:s])
      #50% najbardziej sprawnych Mario mogą się rozmnożyć i zapełnić pozostałe 90% nowej generacji
      s = int((90*populationSize)/100)
      for _ in range(s):
         marioMom = random.choice(population[:int(populationSize/2)])
         marioDad = random.choice(population[:int(populationSize/2)])
         marioChild = mate(marioMom, marioDad, tabLen)
         testMario(env, marioChild)
         newGeneration.append(marioChild)
      """
      marioRouletteSelection = calculateProbability(population, sumDistance)
      sumDistance = 0
      #Selekcja i krzyzowanie
      for _ in range(populationSize):
         prob = random.random()
         newMario = Mario()
         if prob < 0.3:
            newMario = random.choice(marioRouletteSelection)
         else:
            marioMom = random.choice(marioRouletteSelection)
            marioDad = random.choice(marioRouletteSelection)
            newMario = mate(marioMom, marioDad, tabLen)
            newMario.mutate(tabLen)
            testMario(env, newMario)
         newGeneration.append(newMario)
         sumDistance += abs(newMario.distance)

      population = newGeneration
      generation += 1

   print(f"Generacja = {generation}, dystans Mario = {population[0].distance}")

   env.close()

def runSavedMario(generationNumber):
   hatLength = 3
   env = gym.make("ALE/DonkeyKong-v5", render_mode="human")
   observation, info = env.reset(seed=42)
   savedMario = Mario()
   savedMario.readFromFile(generationNumber)
   observation, reward, terminated, truncated, info = env.step(1)
   for gene in savedMario.genes:
      action = int(gene)
      red_location = findRed(observation)
      if red_location is None:
         continue
      for i in range(red_location[1] - 6, red_location[1] + hatLength + 7):
         for j in range(red_location[0], red_location[0] + 10):
            if i < 0 or j < 0:
               continue
            if(observation[j][i][0] == 236 and observation[j][i][1] == 200 and observation[j][i][2] == 96):
               if i > red_location[1]:
                  #print("Prawa")
                  action = 11
                  break
               else:
                  #print("Lewa")
                  action = 12
                  break
      observation, reward, terminated, truncated, info = env.step(action)
      if terminated or truncated or info["lives"] < 2:
         env.close()
         break

if __name__ == '__main__':
   #env = gym.make("ALE/DonkeyKong-v5", render_mode="human")
   train()
   #runSavedMario(12)


   public override void Startup() {
            try
            {
                Console.WriteLine("Starting OPCNodeManager.");

                DefaultNamespaceIndex = AddNamespaceUri("http://yourorganisation.org/OPC/");

                Console.WriteLine("Loading the OPC Model.");
                ImportUaNodeset(Assembly.GetEntryAssembly(), "opc.xml");

                VariableNode automat = SetVariableConfiguration(
                            new NodeId(5005, 2),
                            new QualifiedName("Automat", 2),
                            NodeHandleType.ExternalPolled,
                            new SystemAddress() { Address = 1, Offset = 1 });

                VariableNode licznik = SetVariableConfiguration(
                            new NodeId(5005, 2),
                            new QualifiedName("Licznik", 2),
                            NodeHandleType.ExternalPolled,
                            new SystemAddress() { Address = 2, Offset = 2});

                VariableNode poziom = SetVariableConfiguration(
                            new NodeId(5005, 2),
                            new QualifiedName("Poziom", 2),
                            NodeHandleType.ExternalPolled,
                            new SystemAddress() { Address = 3, Offset = 3 });

                VariableNode przeplywP1 = SetVariableConfiguration(
                            new NodeId(5004, 2),
                            new QualifiedName("Przeplyw", 2),
                            NodeHandleType.ExternalPolled,
                            new SystemAddress() { Address = 4, Offset = 4 });

                VariableNode stanP1 = SetVariableConfiguration(
                            new NodeId(5004, 2),
                            new QualifiedName("Stan", 2),
                            NodeHandleType.ExternalPolled,
                            new SystemAddress() { Address = 5, Offset = 5 });

                VariableNode wylP1 = SetVariableConfiguration(
                            new NodeId(5004, 2),
                            new QualifiedName("Wyl", 2),
                            NodeHandleType.ExternalPolled,
                            new SystemAddress() { Address = 6, Offset = 6 });
            }
        }


protected override void Read(RequestContext context, TransactionHandle transaction, IList<NodeAttributeOperationHandle> operationHandles, IList<ReadValueId> settings) {
   for (int i = 0; i < operationHandles.Count; i++) {
      DataValue data = null;
      SystemAddress address = operationHandles[i].NodeHandle.UserData as SystemAddress;
      if (address != null) {
         object value = false;
         if (valuesDict.ContainsKey(operationHandles[i].NodeId.Identifier.GetHashCode()))
            value = valuesDict[operationHandles[i].NodeId.Identifier.GetHashCode()];
         data = new DataValue(new Variant(value, null), DateTime.UtcNow);
         if (!String.IsNullOrEmpty(settings[i].IndexRange) || !QualifiedName.IsNull(settings[i].DataEncoding))
         data = ApplyIndexRangeAndEncoding(operationHandles[i].NodeHandle, data, settings[i].IndexRange, settings[i].DataEncoding);
      }
      if (data == null)
         data = new DataValue(new StatusCode(StatusCodes.BadNodeIdUnknown));
      ((ReadCompleteEventHandler)transaction.Callback)(operationHandles[i], transaction.CallbackData, data, false);
   }
}

protected override void Write( RequestContext context, transactionHandle transaction, IList<NodeAttributeOperationHandle> operationHandles, IList<WriteValue> settings) {
   for (int i = 0; i < operationHandles.Count; ii++) {
      StatusCode error = StatusCodes.Good;
      SystemAddress address = operationHandles[i].NodeHandle.UserData as SystemAddress;
      if (address != null)
         if (!String.IsNullOrEmpty(settings[ii].IndexRange))
            error = StatusCodes.BadIndexRangeInvalid;
      else
      error = StatusCodes.BadNodeIdUnknown;
      valuesDict[operationHandles[i].NodeId.Identifier.GetHashCode()] = settings[i].Value.Value;
      ((WriteCompleteEventHandler)transaction.Callback)( operationHandles[i], transaction.CallbackData,  error, false);
   }
}
