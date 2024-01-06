import { Taxi } from "./taxi";

export class BasicTaxi implements Taxi {
  calculateCost(): number {
    return 10; // Basic cost
  }
}
