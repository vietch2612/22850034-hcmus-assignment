import { Taxi } from "./taxi";

export abstract class TaxiDecorator implements Taxi {
  protected decoratedTaxi: Taxi;

  constructor(taxi: Taxi) {
    this.decoratedTaxi = taxi;
  }

  abstract calculateCost(): number;
}
