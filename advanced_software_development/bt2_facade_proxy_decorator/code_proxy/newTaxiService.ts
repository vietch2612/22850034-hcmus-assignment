import { TaxiService } from "./taxiService";

export class RealTaxiService implements TaxiService {
  bookRide(start: string, end: string): string {
    return `Ride booked from ${start} to ${end}`;
  }
}
