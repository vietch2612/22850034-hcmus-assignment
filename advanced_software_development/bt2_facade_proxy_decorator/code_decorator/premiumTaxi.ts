import { TaxiDecorator } from "./taxiDecorator";

export class PremiumTaxi extends TaxiDecorator {
  calculateCost(): number {
    // Adding luxury cost
    return this.decoratedTaxi.calculateCost() + 20;
  }
}
