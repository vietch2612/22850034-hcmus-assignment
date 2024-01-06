import { Taxi } from "./taxi";
import { BasicTaxi } from "./basicTaxi";
import { PremiumTaxi } from "./premiumTaxi";
import { WiFiDecorator } from "./wiFiDecorator";

const basicTaxi: Taxi = new BasicTaxi();
console.log("Basic Taxi Cost:", basicTaxi.calculateCost());

const premiumTaxi: Taxi = new PremiumTaxi(new BasicTaxi());
console.log("Premium Taxi Cost:", premiumTaxi.calculateCost());

const premiumTaxiWithWiFi: Taxi = new WiFiDecorator(
  new PremiumTaxi(new BasicTaxi())
);
console.log(
  "Premium Taxi with WiFi Cost:",
  premiumTaxiWithWiFi.calculateCost()
);
