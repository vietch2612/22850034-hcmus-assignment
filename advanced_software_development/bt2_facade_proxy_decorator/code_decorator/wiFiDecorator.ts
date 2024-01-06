import { TaxiDecorator } from "./taxiDecorator";

export class WiFiDecorator extends TaxiDecorator {
  calculateCost(): number {
    // Adding WiFi cost
    return this.decoratedTaxi.calculateCost() + 5;
  }
}
