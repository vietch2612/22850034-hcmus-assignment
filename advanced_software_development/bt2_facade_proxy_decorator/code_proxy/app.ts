import { TaxiService } from "./taxiService";
import { ProxyTaxiService } from "./proxyTaxiService";

// Usage
const taxiService: TaxiService = new ProxyTaxiService();

console.log(taxiService.bookRide("Origin", "Destination")); // Valid booking
console.log(taxiService.bookRide("A", "A")); // Invalid booking
